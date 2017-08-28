/*
 *  circle.h - Empty Shape
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

#ifndef __GEOM_HELPERS__CIRCLE_H__1B437DBE
#define __GEOM_HELPERS__CIRCLE_H__1B437DBE

#include <ostream>
#include <algorithm>

#include <2geom/point.h>

namespace Geom {

class Circle {
public:
    Circle(Geom::Point pos_, double radius_) :
        pos(pos_),
        radius(radius_)
    {}
    Circle(double radius) :
        Circle({0, 0}, radius)
    {}
    Circle() :
        Circle(0)
    {}
public:
    Geom::Point pos;
    double radius;
};

std::ostream& operator<<(std::ostream& stream, Circle const& circle);

}

#endif
