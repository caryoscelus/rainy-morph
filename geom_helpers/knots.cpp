/*
 *  knots.cpp - Geom paths <-> bezier knots conversion
 *  Copyright (C) 2017 caryoscelus
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <geom_helpers/knots.h>

#include <2geom/path-sink.h>

namespace Geom {

std::vector<Knot> path_to_knots(Geom::Path const& path) {
    std::vector<Knot> result;
    Geom::Point old_tg;
    Geom::Point next_point;
    for (auto const& segment : path) {
        auto maybe_bezier = dynamic_cast<Geom::CubicBezier const*>(&segment);
        if (maybe_bezier == nullptr) {
            std::cerr << "not curve" << std::endl;
            // throw
            continue;
        }
        auto const& bezier = *maybe_bezier;
        auto controls = bezier.controlPoints();
        result.emplace_back(controls[0], old_tg, controls[1]);
        old_tg = controls[2];
        next_point = controls[3];
    }
    result.emplace_back(next_point, old_tg, Geom::Point());
    return result;
}

Geom::Path knots_to_path(std::vector<Knot> const& knots) {
    if (knots.size() < 2) return Geom::Path();

    auto builder = Geom::PathBuilder();
    Geom::Point first_point;
    Geom::Point last_point;
    Geom::Point old_tg;
    bool first = true;
    for (auto const& knot : knots) {
        if (first) {
            first = false;
            first_point = knot.pos;
            builder.moveTo(knot.pos);
        } else {
            builder.curveTo(old_tg, knot.tg1, knot.pos);
        }
        old_tg = knot.tg2;
        last_point = knot.pos;
    }
//     std::cerr << first_point << " " << last_point << std::endl;
    if (first_point == last_point)
        builder.closePath();
    builder.flush();
    return builder.peek().at(0);
}

} // namespace Geom
