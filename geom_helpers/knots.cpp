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

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom_helpers/knots_io.h>

#include <2geom/path-sink.h>
#include <2geom/svg-path-parser.h>
#include <2geom/svg-path-writer.h>

using namespace fmt::literals;

namespace Geom {

BezierKnots path_to_knots(Geom::Path const& path) {
    BezierKnots result;
    result.closed = path.closed();

    if (path.size_default() < 1)
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
        result.knots.push_back(Knot::from_absolute(controls[0], old_tg, controls[1]));
        old_tg = controls[2];
        next_point = controls[3];
    }
    if (!path.closed()) {
        result.knots.push_back(Knot::from_absolute(next_point, old_tg, next_point));
    } else {
        result.knots[0].tg1 = old_tg-result.knots[0].pos;
    }
    return result;
}

Geom::Path knots_to_path(BezierKnots const& knots) {
    if (knots.size() < 1) return Geom::Path();

    auto builder = Geom::PathBuilder();
    Geom::Knot first_knot;
    Geom::Point old_tg;
    Geom::Point old_pos;
    bool first = true;
    for (auto const& knot : knots.knots) {
        if (first) {
            first = false;
            first_knot = knot;
            builder.moveTo(knot.pos);
        } else {
            builder.curveTo(old_pos+old_tg, knot.pos+knot.tg1, knot.pos);
        }
        old_pos = knot.pos;
        old_tg = knot.tg2;
    }
    if (knots.closed) {
        builder.curveTo(old_pos+old_tg, first_knot.pos+first_knot.tg1, first_knot.pos);
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

Geom::BezierKnots parse_named_knots(std::string const& str) {
    std::istringstream stream(str);
    std::string svg_path, keys;
    std::getline(stream, svg_path, '@');
    std::getline(stream, keys, '@');
    auto path = Geom::svg_to_knots(svg_path);
    unsigned index = 0;
    std::istringstream keystream(keys);
    while (keystream.good() && index < path.size()) {
        std::string key;
        std::getline(keystream, key, ',');
        path.knots[index].uid = key;
        ++index;
    }
    return path;
}

std::string knot_names_to_str(Geom::BezierKnots const& knots) {
    std::ostringstream stream;
    for (auto const& knot : knots.knots) {
        stream << knot.uid << ",";
    }
    return stream.str();
}

std::string named_knots_to_str(Geom::BezierKnots const& knots) {
    return knots_to_svg(knots)+" @"+knot_names_to_str(knots)+";";
}

Knot parse_knot(std::string const& /*string*/) {
    throw std::runtime_error("Knot parsing not implemented");
}

std::ostream& operator<<(std::ostream& stream, Knot const& knot) {
    return stream << "BezierKnot({}, {}, {})"_format(knot.pos, knot.tg1, knot.tg2);
}

} // namespace Geom
