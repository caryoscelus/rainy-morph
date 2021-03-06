/*  knots.h - Geom paths <-> bezier knots conversion
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

#ifndef GEOM_HELPERS_KNOTS_H_4FAE1DD9_9BA9_5F2C_91C9_8B79D2006BE6
#define GEOM_HELPERS_KNOTS_H_4FAE1DD9_9BA9_5F2C_91C9_8B79D2006BE6

#include <2geom/path.h>

namespace Geom {

struct Knot {
    using Id = std::string;
    Point pos;
    Point tg1;
    Point tg2;
    Id uid;

    /// Implicit empty default constructor
    Knot() = default;

    /// Construct from point and it's tangents (in relative coords)
    explicit Knot(Point pos_, Point tg1_=Point(), Point tg2_=Point(), Id uid_="") :
        pos(pos_), tg1(tg1_), tg2(tg2_), uid(uid_)
    {}

    /// Construct from absolute coordinates
    static Knot from_absolute(Point pos, Point atg1, Point atg2, Id uid="") {
        return Knot(pos, atg1-pos, atg2-pos, uid);
    }

    bool operator==(Knot const& other) const {
        return pos == other.pos
            && tg1 == other.tg1
            && tg2 == other.tg2
            && uid == other.uid;
    }
    bool operator!=(Knot const& other) const {
        return !(*this == other);
    }
};

class BezierKnots {
public:
    /// Implicit default constructor - empty path
    BezierKnots() :
        BezierKnots{{}}
    {}

    /// Explicit constructor from knot vector
    explicit BezierKnots(std::vector<Knot> knots_, bool closed_=true) :
        knots(knots_), closed(closed_)
    {}

    bool operator==(BezierKnots const& other) const {
        return closed == other.closed
            && knots == other.knots;
    }
    bool operator!=(BezierKnots const& other) const {
        return !(*this == other);
    }

    template <typename... Ts>
    void emplace_back(Ts&&... args) {
        knots.emplace_back(std::forward<Ts>(args)...);
    }

    size_t size() const {
        return knots.size();
    }
    bool empty() const {
        return size() == 0;
    }
    Knot const& first() const {
        // TODO: throw?
        return knots[0];
    }
    Knot const& last() const {
        return knots[size()-1];
    }
    Knot& first() {
        return knots[0];
    }
    Knot& last() {
        return knots[size()-1];
    }

public:
    std::vector<Knot> knots;
    bool closed;
};

BezierKnots path_to_knots(Geom::Path const& path);
Geom::Path knots_to_path(BezierKnots const& knots);

BezierKnots svg_to_knots(std::string const& str);
BezierKnots svg_to_knots(char const* str);
std::string knots_to_svg(BezierKnots const& knots);

} // namespace Geom

#endif
