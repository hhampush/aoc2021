#include <bits/stdc++.h>
void filter_list(std::vector<std::string>& lines, const char value, const int pos) { for (auto it = lines.begin(); it != lines.end(); it++) { if (it->at(pos) != value) lines.erase(it--); }}

std::tuple<int,int> count_in_col(std::vector<std::string>& lines, const int col, std::string row_string = "") {
    for (auto &line : lines) { row_string += line.at(col); }
    return std::tuple<int,int>(count(row_string.begin(), row_string.end(), '0'), count(row_string.begin(), row_string.end(), '1')); }

std::vector<std::string> check_scrub_power(std::vector<std::string> lines, const bool scrub_mode) {
    for (int i = 0; i < 12 && lines.size() > 1; i++) {
        if (auto nums = count_in_col(lines, i); get<1>(nums) >= get<0>(nums)) filter_list(lines, (scrub_mode ? '0' : '1'), i);
        else filter_list(lines, (scrub_mode ? '1' : '0'), i);
    } return lines; }

int main() {
    auto [gamma, epsilon, lines, part1] = std::tuple{std::string(), std::string(), std::vector<std::string>{}, (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos)};
    for (auto [file, line] = std::tuple{std::ifstream("input.txt"), std::string()}; std::getline(file, line);) { lines.push_back(line.substr(0, 12)); }
    for (int i = 0; i < 12; i++) { auto nums = count_in_col(lines, i); gamma.append(get<1>(nums) > get<0>(nums) ? "1" : "0"), epsilon.append(get<1>(nums) > get<0>(nums) ? "0" : "1"); }
    if (part1) std::cout << std::stoi(gamma, nullptr, 2) * std::stoi(epsilon, nullptr, 2) << std::endl;
    else std::cout << std::stoi(check_scrub_power(lines, false).at(0), nullptr, 2) * std::stoi(check_scrub_power(lines, true).at(0), nullptr, 2) << std::endl; }