/*
 *  knots_io.h - BezierKnots parse&format
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

#ifndef __GEOM_HELPERS__KNOTS_IO_H__36107894
#define __GEOM_HELPERS__KNOTS_IO_H__36107894

#include <ostream>

#include "knots.h"

namespace Geom {

Geom::BezierKnots parse_named_knots(std::string const& string);
std::string named_knots_to_str(Geom::BezierKnots const& knots);

inline std::ostream& operator<<(std::ostream& stream, Geom::BezierKnots const& knots) {
    return stream << named_knots_to_str(knots);
}

} // namespace Geom

#endif
