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

TEST_CASE("Converting path to knot list", "") {
    auto svg = "m 27,173 c 187,-91 221,282 0,0 z";
    auto path = Geom::parse_svg_path(svg).at(0);
    auto knots = Geom::path_to_knots(path);
    auto path_c = Geom::knots_to_path(knots);
    REQUIRE(paths_almost_equal(path, path_c));
}
