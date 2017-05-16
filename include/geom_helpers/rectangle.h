/*
 *  null_shape.h - Empty Shape
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

#ifndef __GEOM_HELPERS__RECTANGLE_H__CB6A232E
#define __GEOM_HELPERS__RECTANGLE_H__CB6A232E

#include <ostream>
#include <algorithm>

#include <2geom/point.h>

namespace Geom {

class Rectangle {
public:
    Rectangle(Geom::Point pos_, Geom::Point size_) :
        pos(pos_),
        size(size_)
    {}
    Rectangle(Geom::Point size) :
        Rectangle({0, 0}, size)
    {}
    Rectangle() :
        Rectangle({0, 0})
    {}
public:
    static Rectangle fromTwoPoints(Geom::Point a, Geom::Point b) {
        auto pos = Geom::Point(
            std::min(a.x(), b.x()),
            std::min(a.y(), b.y())
        );
        auto size = Geom::Point(
            std::max(a.x(), b.x()),
            std::max(a.y(), b.y())
        ) - pos;
        return Rectangle(pos, size);
    }
public:
    Geom::Point pos;
    Geom::Point size;
};

std::ostream& operator<<(std::ostream& stream, Rectangle const& rect);

}

#endif
