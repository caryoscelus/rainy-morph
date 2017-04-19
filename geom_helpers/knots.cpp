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
#include <2geom/svg-path-parser.h>
#include <2geom/svg-path-writer.h>

namespace Geom {

BezierKnots path_to_knots(Geom::Path const& path) {
    BezierKnots result;
    result.closed = path.closed();

    if (path.size_open() == 0)
        return result;

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
        result.knots.emplace_back(controls[0], old_tg, controls[1]);
        old_tg = controls[2];
        next_point = controls[3];
    }
    result.knots[0].tg1 = old_tg;
    return result;
}

Geom::Path knots_to_path(BezierKnots const& knots) {
    if (knots.size() < 1) return Geom::Path();

    auto builder = Geom::PathBuilder();
    Geom::Knot first_knot;
    Geom::Point old_tg;
    bool first = true;
    for (auto const& knot : knots.knots) {
        if (first) {
            first = false;
            first_knot = knot;
            builder.moveTo(knot.pos);
        } else {
            builder.curveTo(old_tg, knot.tg1, knot.pos);
        }
        old_tg = knot.tg2;
    }
    builder.curveTo(old_tg, first_knot.tg1, first_knot.pos);
    if (knots.closed) {
        builder.closePath();
    }
    builder.flush();
    return builder.peek().at(0);
}

BezierKnots svg_to_knots(std::string const& str) {
    return svg_to_knots(str.c_str());
}

BezierKnots svg_to_knots(char const* str) {
    return path_to_knots(Geom::parse_svg_path(str).at(0));
}

std::string knots_to_svg(BezierKnots const& knots) {
    return Geom::write_svg_path({knots_to_path(knots)});
}

} // namespace Geom
