/*
 *  compare.cpp - Geom paths comparison
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

#include <geom_helpers/compare.h>

const double EPS = 1.0/32;

namespace Geom {

bool curves_almost_equal(Geom::Curve const& a, Geom::Curve const& b) {
    return a.isNear(b, EPS);
}

bool paths_almost_equal(Geom::Path const& a, Geom::Path const& b) {
    if (a == b)
        return true;
    if (a.closed() != b.closed())
        return false;
    if (a.size() != b.size())
        return false;
    for (unsigned i = 0; i < a.size(); ++i) {
        if (!curves_almost_equal(a[i], b[i]))
            return false;
    }
    return true;
}

} // namespace Geom
