/*
 *  split.h - Geom path splitting helper
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

#ifndef __GEOM_HELPERS__SPLIT_H__5830A9BC
#define __GEOM_HELPERS__SPLIT_H__5830A9BC

#include <2geom/path.h>

namespace Geom {

/**
 * Split path at `div` times and then merge it back.
 *
 * Returns path identical to original, but containing additional subdivisions
 */
Geom::Path split_and_merge_path(Geom::Path const& path, std::vector<Geom::PathTime> const& div);

} // namespace Geom

#endif
