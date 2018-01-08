/*  bones.cpp - test bones
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

#include <catch.hpp>

#include <2geom/transforms.h>

#include <geom_helpers/bones.h>

using namespace Geom;
using namespace bones;

TEST_CASE("Zero bone difference", "[bones]") {
    auto bone_zero_1x = Bone{ {0, 0}, {1, 0} };
    auto bone_zero_2y = Bone{ {0, 0}, {0, 2} };
    CHECK(bone_diff(bone_zero_1x, bone_zero_2y) == Scale(2, 1)*Rotate({0, 1}));
    CHECK(bone_diff(bone_zero_1x, bone_zero_2y) == bone_diff(bone_zero_2y, bone_zero_1x).inverse());
}

TEST_CASE("Other bones", "[bones]") {
    auto bone_1_2 = Bone{ {1, 1}, {1, 0} };
    auto bone_2_1 = Bone{ {2, 0}, {-1, 0} };
    CHECK(bone_diff(bone_1_2, bone_2_1) == Translate(-1, -1)*Rotate({-1, 0})*Translate(2, 0));
}
