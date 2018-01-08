/*  bones.h - bones transformation <-> affine
 *  Copyright (C) 2018 caryoscelus
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

#ifndef GEOM_HELPERS_BONES_H_965E46EF_49F3_5A61_AD84_94FC61357F5D
#define GEOM_HELPERS_BONES_H_965E46EF_49F3_5A61_AD84_94FC61357F5D

#include <ostream>

#include <2geom/affine.h>

namespace Geom::bones {

struct Bone : public std::pair<Point, Point> {
    Bone() :
        std::pair<Point, Point>()
    {}
    Bone(Point a, Point b) :
        std::pair<Point, Point>(a, b)
    {}
};

Affine rot_scale_2(Point const& a, Point const& b);

Affine bone_diff(Bone const& a, Bone const& b);

std::ostream& operator<<(std::ostream& stream, Bone const& bone);

} // namespace Geom::bones

#endif
