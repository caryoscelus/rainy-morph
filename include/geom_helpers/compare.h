/*
 *  compare.h - Geom paths comparison
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

#ifndef __GEOM_HELPERS__COMPARE_H__8DA5806E
#define __GEOM_HELPERS__COMPARE_H__8DA5806E

#include <2geom/path.h>

namespace Geom {

bool curves_almost_equal(Geom::Curve const& a, Geom::Curve const& b);
bool paths_almost_equal(Geom::Path const& a, Geom::Path const& b);

} // namespace Geom

#endif
