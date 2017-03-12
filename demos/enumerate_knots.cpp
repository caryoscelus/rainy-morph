/*
 *  enumerate_knots.cpp - knot enumeration utility
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
#include <morphing/morphing.h>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <iostream>
#include <string>

using namespace fmt::literals;

const std::string tmplt = R"TMPLT(<text x="{0}" y="{1}" font-size="3px" fill="red">{2}</text>
)TMPLT";

void enumerate_knots(std::string const& svg) {
    auto path = Geom::svg_to_knots(svg.c_str());
    unsigned index = 0;
    for (auto const& knot : path.knots) {
        fmt::print(tmplt, knot.pos.x(), knot.pos.y(), index);
        ++index;
    }
}

int main(int argc, char** argv) {
    std::string svg;
    if (argc < 2) {
        fmt::print(std::cerr, "Usage: {} <svg-path>\n", argv[0]);
        return 1;
    } else {
        svg = argv[1];
        if (argc > 2) {
            fmt::print(std::cerr, "Extra arguments ignored.\n");
        }
    }
    enumerate_knots(svg);
    return 0;
}
