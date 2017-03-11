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

#include <morphing/morphing.h>
#include <geom_helpers/knots.h>

namespace morphing {

using Geom::Knot;
using Geom::BezierKnots;

Knot knot_average(Knot const& a, Knot const& b, double amount) {
    auto a_amount = 1.0-amount;
    return Knot(a.pos*a_amount + b.pos*amount,
                a.tg1*a_amount + b.tg1*amount,
                a.tg2*a_amount + b.tg2*amount);
}

BezierKnots simple_average(BezierKnots const& a, BezierKnots const& b, double amount) {
    if (a.closed != b.closed)
        throw "a nd b have different closedness";
    if (a.knots.size() != b.knots.size())
        throw "a and b have different length";
    BezierKnots result;
    for (int i = 0; i < a.knots.size(); ++i) {
        result.knots.push_back(knot_average(a.knots[i], b.knots[i], amount));
    }
    return result;
}

} // namespace morphing
