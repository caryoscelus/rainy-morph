/*
 *  morphing.cpp - path morphing
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

#ifndef __MORPHING__MORPHING_H__1A39CB22
#define __MORPHING__MORPHING_H__1A39CB22

#include <geom_helpers/knots.h>

namespace morphing {

Geom::Knot knot_average(Geom::Knot const& a, Geom::Knot const& b, double amount);
std::vector<Geom::Knot> simple_average(std::vector<Geom::Knot> const& a, std::vector<Geom::Knot> const& b, double amount);

} // namespace morphing

#endif
