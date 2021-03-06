/*
 *  convert.cpp - test bezier path <-> knot list conversion
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

#include <catch.hpp>

#include <2geom/svg-path-parser.h>

#include <geom_helpers/compare.h>
#include <geom_helpers/knots.h>

void test_convert(std::string const& svg, std::string const& svg_t = "") {
    auto path = Geom::parse_svg_path(svg.c_str()).at(0);
    auto knots = Geom::path_to_knots(path);
    if (knots.closed)
        CHECK(knots.size() == path.size_default());
    CHECK(knots.closed == path.closed());
    auto path_c = Geom::knots_to_path(knots);
    auto path_t = svg_t == "" ? path : Geom::parse_svg_path(svg_t.c_str()).at(0);
    CHECK(Geom::paths_almost_equal(path_c, path_t));
}

TEST_CASE("Converting closed path to knot list", "[convert]") {
    test_convert("m 27,173 c 187,-91 221,282 0,0 z");
}

TEST_CASE("Converting open path to knot list", "[convert]") {
    test_convert("m 27,173 c 187,-91 221,282 0,0");
}

TEST_CASE("Converting another open path to knot list", "[convert]") {
    test_convert("m 27,173 c 187,-91 221,282 20,40");
}

TEST_CASE("Converting quadratic path to knot list", "[convert]") {
    test_convert("M 0,30 Q 30,60 90,0", "M 0,30 C 20,50 50,40 90,0");
}

TEST_CASE("Converting linear path to knot list", "[convert]") {
    test_convert("m 27,173 l 20,40", "m 27,173 c 0,0 20,40 20,40");
}
