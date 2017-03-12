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
#include <geom_helpers/split.h>

#include <set>
#include <experimental/numeric>

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

using MorphingKeys = std::vector<std::pair<Knot::Id, size_t>>;

void read_keys(BezierKnots const& src, MorphingKeys& keys, std::set<Knot::Id>& keyset) {
    size_t index = 0;
    for (auto const& knot : src.knots) {
        if (!knot.uid.empty()) {
            keys.emplace_back(knot.uid, index);
            keyset.insert(knot.uid);
        }
        ++index;
    }
}

void intersect_keys(BezierKnots const& a, BezierKnots const& b, MorphingKeys& keys_a, MorphingKeys& keys_b) {
    MorphingKeys all_a, all_b;
    std::set<Knot::Id> set_a, set_b;
    read_keys(a, all_a, set_a);
    read_keys(b, all_b, set_b);
    auto filter = [&set_a, &set_b](auto pair) {
        return
            set_a.find(pair.first) != std::end(set_a) &&
            set_b.find(pair.first) != std::end(set_b);
    };
    std::copy_if(
        std::begin(all_a), std::end(all_a),
        std::back_inserter(keys_a),
        filter
    );
    std::copy_if(
        std::begin(all_b), std::end(all_b),
        std::back_inserter(keys_b),
        filter
    );
}

template<typename I>
std::vector<I> get_indexes(I prev, I curr, I amount) {
    std::vector<I> result;
    if (prev < curr) {
        for (auto i = prev+1; i <= curr; ++i)
            result.push_back(i);
    } else {
        for (auto i = prev+1; i < amount; ++i)
            result.push_back(i);
        for (size_t i = 0; i <= curr; ++i)
            result.push_back(i);
    }
    return result;
}

void calculate_split(std::vector<Geom::PathTime>& result, std::vector<size_t> indexes, unsigned split) {
    std::cerr << "calculate split " << split << std::endl;
    for (auto index : indexes) {
        for (unsigned i = 1; i < split; ++i) {
            result.push_back(index + 1.0*i/split);
        }
    }
}

void prepare_average(BezierKnots const& a, BezierKnots const& b, BezierKnots& target_a, BezierKnots& target_b) {
    // collect keys
    // intersect keys
    MorphingKeys keys_a;
    MorphingKeys keys_b;
    intersect_keys(a, b, keys_a, keys_b);
    if (keys_a.size() != keys_b.size())
        throw "Different size";
    if (keys_a.empty())
        throw "No common keys";
    // for each interval: calculate split
    std::vector<Geom::PathTime> div_a;
    std::vector<Geom::PathTime> div_b;
    auto prev_a = keys_a.rbegin()->second;
    auto prev_b = keys_b.rbegin()->second;
    auto key_a = std::begin(keys_a);
    auto key_b = std::begin(keys_b);
    for (; key_a != std::end(keys_a); ++key_a, ++key_b) {
        std::vector<size_t> indexes_a = get_indexes(prev_a, key_a->second, a.size());
        std::vector<size_t> indexes_b = get_indexes(prev_b, key_b->second, b.size());
        auto a_size = indexes_a.size();
        auto b_size = indexes_b.size();
        if (a_size == b_size) {
            // 1 : 1 - trivial case - do nothing
        } else if (a_size % b_size == 0) {
            // k : 1 - only split b
            calculate_split(div_b, indexes_b, a_size/b_size);
        } else if (b_size % a_size == 0) {
            // 1 : k - only split a
            calculate_split(div_a, indexes_a, b_size/a_size);
        } else {
            auto lcm = std::experimental::lcm(a_size, b_size);
            calculate_split(div_a, indexes_a, lcm/a_size);
            calculate_split(div_b, indexes_b, lcm/b_size);
        }
    }
    // apply split
    auto path_a = Geom::knots_to_path(a);
    auto path_b = Geom::knots_to_path(b);
    if (div_a.size() > 0) {
        target_a = Geom::path_to_knots(Geom::split_and_merge_path(path_a, div_a));
        target_a.closed = a.closed;
    } else {
        target_a = a;
    }
    if (div_b.size() > 0) {
        target_b = Geom::path_to_knots(Geom::split_and_merge_path(path_b, div_b));;
        target_b.closed = b.closed;
    } else {
        target_b = b;
    }
}

} // namespace morphing
