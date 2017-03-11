/*
 *  knots.h - Geom paths <-> bezier knots conversion
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

#ifndef __GEOM_HELPERS__KNOTS_H__B3B45F40
#define __GEOM_HELPERS__KNOTS_H__B3B45F40

#include <2geom/path.h>

namespace Geom {

struct Knot {
    Geom::Point pos;
    Geom::Point tg1;
    Geom::Point tg2;
    std::string uid;
    Knot(Geom::Point pos_, Geom::Point tg1_, Geom::Point tg2_, std::string uid_="") :
        pos(pos_), tg1(tg1_), tg2(tg2_), uid(uid_)
    {}
};

struct BezierKnots {
    std::vector<Knot> knots;
    bool closed;
    explicit BezierKnots(std::vector<Knot> knots_={}, bool closed_=true) :
        knots(knots_), closed(closed_)
    {}
};

BezierKnots path_to_knots(Geom::Path const& path);
Geom::Path knots_to_path(BezierKnots const& knots);

BezierKnots svg_to_knots(char const* str);
std::string knots_to_svg(BezierKnots const& knots);

} // namespace Geom

#endif
