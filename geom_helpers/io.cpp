/*
 *  io.cpp - Geom io
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

#include <sstream>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom_helpers/point_io.h>
#include <geom_helpers/rectangle.h>
#include <geom_helpers/circle.h>

using namespace fmt::literals;

namespace Geom {

Point parse_point(std::string const& string) {
    std::istringstream stream(string);
    if (stream.get() == '(') {
        double x;
        stream >> x;
        if (stream.get() == ',') {
            double y;
            stream >> y;
            if (stream.get() == ')')
                return Point(x, y);
        }
    }
    throw std::runtime_error("Error while parsing Point '{}'"_format(string));
}

std::ostream& operator<<(std::ostream& stream, Rectangle const& rect) {
    return stream << "Rectangle(pos={}, size={})"_format(rect.pos, rect.size);
}

std::ostream& operator<<(std::ostream& stream, Circle const& circle) {
    return stream << "Circle(pos={}, radius={})"_format(circle.pos, circle.radius);
}

} // namespace Geom
