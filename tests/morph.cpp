/*
 *  morph.cpp - basic morphing tests
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

#include <geom_helpers/knots.h>
#include <morphing/morphing.h>

TEST_CASE("Simple morphing with equal amount of knots", "") {
    auto src_from = "m 100,100 c 10,10 20,10 20,0 c 20,20 20,10 30,-20 c -10,-10 -30,0 -10,20 c -10,-10 -30,0 -40,0 z";
    auto src_to = "m 100,100 c 20,0 30,-10 30,-30 c 0,-20 -10,-30 -30,-30 c -20,0 -30,10 -30,30 c 0,20 10,30 30,30 z";
    auto path_from = Geom::svg_to_knots(src_from);
    auto path_to = Geom::svg_to_knots(src_to);
    REQUIRE(
        Geom::knots_to_svg(morphing::simple_average(path_from, path_to, 0.0)) ==
        "M 100 100 C 110 110 120 110 120 100 C 140 120 140 110 150 80 C 140 70 120 80 140 100 C 130 90 110 100 100 100 z"
    );
    REQUIRE(
        Geom::knots_to_svg(morphing::simple_average(path_from, path_to, 0.5)) ==
        "M 100 100 C 115 105 125 100 125 85 C 135 85 130 75 125 60 C 110 55 95 65 105 85 C 100 90 95 100 100 100 z"
    );
    REQUIRE(
        Geom::knots_to_svg(morphing::simple_average(path_from, path_to, 1.0)) ==
        "M 100 100 C 120 100 130 90 130 70 S 120 40 100 40 S 70 50 70 70 S 80 100 100 100 z"
    );
}

TEST_CASE("Prepare average", "") {
    SECTION("Simple") {
        auto src_from = "m 100,100 c 60,-40 -40,-20 0,0 z";
        auto src_to = "m 100,100 c 20,0 30,-10 30,-30 c 0,-20 -10,-30 -30,-30 c -20,0 -30,10 -30,30 c 0,20 10,30 30,30 z";
        auto path_from = Geom::svg_to_knots(src_from);
        auto path_to = Geom::svg_to_knots(src_to);
        path_from.knots[0].uid = path_to.knots[0].uid = "main";
        Geom::BezierKnots path_from_fixed;
        Geom::BezierKnots path_to_fixed;
        morphing::prepare_average(path_from, path_to, path_from_fixed, path_to_fixed);
        REQUIRE(path_from_fixed.size() == path_to_fixed.size());
        REQUIRE(path_from_fixed.closed == path_to_fixed.closed);
        std::cerr << Geom::knots_to_svg(morphing::simple_average(path_from_fixed, path_to_fixed, 0.5)) << std::endl;
    }
}
