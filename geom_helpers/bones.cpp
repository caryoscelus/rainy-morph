/*  bones.cpp - bones transformation <-> affine
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

#include <2geom/transforms.h>

#include <geom_helpers/bones.h>

namespace Geom::bones {

Affine rot_scale_2(Point const& a, Point const& b) {
    auto f = a.isZero() ? 0 : b.length() / a.length();
    return Rotate(a).inverse() * Scale(f, 1) * Rotate(b);
}

Affine bone_diff(Bone const& a, Bone const& b) {
    return Translate(-a.first) * rot_scale_2(a.second, b.second) * Translate(b.first);
}

std::ostream& operator<<(std::ostream& stream, Bone const& bone) {
    return stream << "{" << bone.first << ", " << bone.second << "}";
}

} // namespace Geom::bones
