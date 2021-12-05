#include <bits/stdc++.h>

int main() {
    auto [points, regex, total] = std::tuple{std::array<std::array<int, 1000>, 1000>{0}, std::regex("([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)"), 0};
    auto comp_xval = [&](const std::tuple<int,int>& t, const std::tuple<int,int>& t2){ return get<0>(t) < get<0>(t2); };
    auto comp_yval = [&](const std::tuple<int,int>& t, const std::tuple<int,int>& t2){ return get<1>(t) < get<1>(t2); };
    for (auto [file, line, part1, matches] = std::tuple{std::ifstream("input.txt"), std::string(), (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos), std::smatch()}; std::getline(file, line);) {
        if (!std::regex_search(line, matches, regex)) continue;
        for (size_t i = 1; i < matches.size(); i += 4) {
            auto [point, connected_point] = std::tuple{std::tuple<int, int>{std::stoi(matches[i]), std::stoi(matches[i+1])}, std::tuple<int, int>{std::stoi(matches[i+2]), std::stoi(matches[i+3])}};

            if (get<0>(point) == get<0>(connected_point)) { // vertical line
                auto minmax = std::minmax(point, connected_point, comp_yval);
                for (int y = get<1>(get<0>(minmax)); y <= get<1>(get<1>(minmax)); y++) points.at(get<0>(get<0>(minmax))).at(y) += 1;
            }
            else if (get<1>(point) == get<1>(connected_point)) { // horizontal line
                auto minmax = std::minmax(point, connected_point, comp_xval);
                for (int x = get<0>(get<0>(minmax)); x <= get<0>(get<1>(minmax)); x++) points.at(x).at(get<1>(get<0>(minmax))) += 1;
            } else if (!part1) { // diagonal line
                auto minmax = std::minmax(point, connected_point, comp_xval);
                auto [x,y, negative_y_dir] = std::tuple{get<0>(get<0>(minmax)), get<1>(get<0>(minmax)), get<1>(get<0>(minmax)) > get<1>(get<1>(minmax))};
                while (true) {
                    points.at(x).at(y) += 1;
                    if (x <= get<0>(get<1>(minmax))) x++;
                    if (negative_y_dir) {
                        if (y >= get<1>(get<1>(minmax))) y--;
                        if (x > get<0>(get<1>(minmax)) && y < get<1>(get<1>(minmax))) break; }
                    else {
                        if (y <= get<1>(get<1>(minmax))) y++;
                        if (x > get<0>(get<1>(minmax)) && y > get<1>(get<1>(minmax))) break; }}}}}

    for (int y = 0; y < 1000; y++)
        for (int x = 0; x < 1000; x++)
            if (points.at(x).at(y) >= 2) total++;
    std::cout << total << std::endl;
}