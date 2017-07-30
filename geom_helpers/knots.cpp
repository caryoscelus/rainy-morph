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

class BezierKnotsSink : public PathSink {
public:
    BezierKnotsSink() {
        target.knots.emplace_back();
        target.closed = false;
    }
public:
    void moveTo(Point const& p) override {
        if (target.size() > 1)
            throw std::runtime_error("BezierKnots: only continuous paths are supported");
        last_knot().pos = p;
    }
    void lineTo(Point const& p) override {
        last_knot().tg2 = {};
        target.knots.emplace_back(p);
    }
    void quadTo(Point const& c, Point const& p) override {
        last_knot().tg2 = (c - last_knot().pos) * 2/3;
        target.knots.emplace_back(p, (c-p)*2/3);
    }
    void curveTo(Point const& c0, Point const& c1, Point const& p) override {
        last_knot().tg2 = c0 - last_knot().pos;
        target.knots.emplace_back(p, c1-p);
    }
    void arcTo(Coord /*rx*/, Coord /*ry*/, Coord /*angle*/, bool /*large_arc*/, bool /*sweep*/, Point const& /*p*/) override {
        throw std::runtime_error("BezierKnots: arcs are not supported");
    }
    void closePath() override {
        if (target.closed)
            throw std::runtime_error("BezierKnots: can't be closed twice");
        if (target.size() > 1 && last_knot().pos == target.knots[0].pos) {
            target.knots[0].tg1 = last_knot().tg1;
            target.knots.pop_back();
        }
        target.closed = true;
    }
    void flush() override {
    }
public:
    inline BezierKnots get() {
        return target;
    }
private:
    Knot& last_knot() {
        return target.knots[target.size()-1];
    }
private:
    BezierKnots target;
    Point point;
    Point old_tg;
};

BezierKnots path_to_knots(Geom::Path const& path) {
    BezierKnotsSink sink;
    sink.feed(path);
    return sink.get();
}

Geom::Path knots_to_path(BezierKnots const& knots) {
    if (knots.size() < 1) return Geom::Path();

    auto builder = Geom::PathBuilder();
    Geom::Point old_tg;
    Geom::Point old_pos;
    bool first = true;
    for (auto const& knot : knots.knots) {
        if (first) {
            first = false;
            builder.moveTo(knot.pos);
        } else {
            builder.curveTo(old_pos+old_tg, knot.pos+knot.tg1, knot.pos);
        }
        old_pos = knot.pos;
        old_tg = knot.tg2;
    }
    if (knots.closed) {
        auto knot = knots.knots[0];
        builder.curveTo(old_pos+old_tg, knot.pos+knot.tg1, knot.pos);
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
