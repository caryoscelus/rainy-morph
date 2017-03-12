/*
 *  animate_morphing.cpp - morphing animation utility
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

#include <geom_helpers/knots.h>
#include <morphing/morphing.h>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace fmt::literals;

std::string slurp(std::string const& fname) {
    std::ifstream in(fname);
    std::stringstream sstr;
    sstr << in.rdbuf();
    in.close();
    return sstr.str();
}

void parse_keys(std::string const& keys, Geom::BezierKnots& path) {
    auto regex = std::regex("[^,]*");
    std::smatch match;
    std::regex_search(keys, match, regex);
    auto keys_begin = std::sregex_iterator(
        std::begin(keys),
        std::end(keys),
        regex
    );
    unsigned index = 0;
    for (auto key = keys_begin; key != std::sregex_iterator(); ++key) {
        std::cerr << key->str() << std::endl;
        path.knots[index].uid = key->str();
        ++index;
    }
}

void parse_average(std::string const& svg_from,  std::string const& svg_to,
                   std::string const& key_from,  std::string const& key_to,
                   Geom::BezierKnots& path_from, Geom::BezierKnots& path_to) {
    auto p_from = Geom::svg_to_knots(svg_from.c_str());
    auto p_to = Geom::svg_to_knots(svg_to.c_str());
    parse_keys(key_from, p_from);
    parse_keys(key_to, p_to);
    morphing::prepare_average(p_from, p_to, path_from, path_to);
}

void animate(std::string const& fname, unsigned frames) {
    using namespace Geom;
    auto input = slurp(fname);
    std::string base_regex = R"(\{\{([^]*)\}\}@\[([a-zA-Z,]*)\])";
    auto regex = std::regex("\""+base_regex+R"([\n\s]*)"+base_regex+"\"");
    std::smatch match;
    std::regex_search(input, match, regex);
    if (match.empty()) {
        std::cerr << "Failed to detect path to morph" << std::endl;
        return;
    }
    auto svg_from = match[1];
    auto key_from = match[2];
    auto svg_to = match[3];
    auto key_to = match[4];
    BezierKnots path_from;
    BezierKnots path_to;
    parse_average(svg_from, svg_to, key_from, key_to, path_from, path_to);
    for (unsigned frame = 0; frame <= frames; ++frame) {
        auto tween = morphing::simple_average(path_from, path_to, 1.0*frame/frames);
        auto output = std::regex_replace(input, regex, "\""+knots_to_svg(tween)+"\"");
        std::ofstream out("{}.{:0>3}.svg"_format(fname, frame));
        out << output;
        out.close();
    }
}

int main(int argc, char** argv) {
    std::string fname;
    unsigned frames = 12;
    if (argc < 2) {
        fmt::print(std::cerr, "Usage: {} [<file-name> [<frame-count>]]\n", argv[0]);
        fname = "fight-source.svg";
    } else {
        fname = argv[1];
        if (argc >= 3) {
            frames = (unsigned) std::stoi(argv[2]);
            if (argc > 3)
                fmt::print(std::cerr, "Extra arguments ignored.\n");
        }
    }
    animate(fname, frames);
    return 0;
}
