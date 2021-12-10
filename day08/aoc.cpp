#include <bits/stdc++.h>
extern "C" char _binary_input_txt_start;
extern "C" char _binary_input_txt_end;

auto check_overlap(auto& characters, auto& numbers, auto n, auto wanted_overlap) {
    int intersect_count = 0;
    for (auto& c : characters) { if (numbers[n].contains(c)) intersect_count++; }
    return (intersect_count == wanted_overlap);
}

auto i_use_five_segments_who_am_i(auto& characters, auto& numbers) {
    if (check_overlap(characters, numbers, 1,  2) && check_overlap(characters, numbers, 7,  3)) return 3;
    else if (check_overlap(characters, numbers, 1, 1) && check_overlap(characters, numbers, 4, 2)) return 2;
    else return 5;
}

auto i_use_six_segments_who_am_i(auto& characters, auto& numbers) {
    if (check_overlap(characters, numbers, 4, 4)) return 9;
    else if (check_overlap(characters, numbers, 1, 2)) return 0;
    else if (check_overlap(characters, numbers, 7, 3)) return 0;
    else return 6;
}

int main(int argc, char **argv) {
    const auto part1 = (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos);
    std::vector<std::tuple<std::vector<std::string>, std::vector<std::string>>> lines;

    std::istringstream input(std::string(&_binary_input_txt_start, &_binary_input_txt_end - &_binary_input_txt_start));
    std::string line;
    while (getline(input, line)) {
        std::vector<std::string> signal_pat{};
        std::vector<std::string> digits{};
        auto del_pos = line.find('|');
        std::istringstream a(line.substr(0, del_pos - 1));
        std::istringstream b(line.substr(del_pos + 2, line.length()));
        while (!a.eof()) {
            std::string token;
            a >> token;
            signal_pat.push_back(token);
        }
        while (!b.eof()) {
            std::string token;
            b >> token;
            digits.push_back(token);
        }
        lines.push_back(std::tuple{signal_pat, digits});
    }

    auto sum = 0;
    for (auto &line : lines) {
        std::array<std::set<char>, 10> numbers{};
        for (auto &s : get<0>(line)) {
            if (s.length() == 2) for (auto& c: s) numbers[1].insert(c);
            else if (s.length() == 3) for (auto& c: s) numbers[7].insert(c);
            else if (s.length() == 4) for (auto& c: s) numbers[4].insert(c);
            else if (s.length() == 7) for (auto& c: s) numbers[8].insert(c);
        }

        std::string number("");
        for (auto &s: get<1>(line)) {
            if (part1)  {
                if (s.length() == 2) sum++;
                else if (s.length() == 3) sum++;
                else if (s.length() == 4) sum++;
                else if (s.length() == 7) sum++;
                continue;
            }

            std::set<char> characters{};
            for (char& c : s) characters.insert(c);

            if (s.length() == 2) number += "1";
            else if (s.length() == 3) number += "7";
            else if (s.length() == 4) number += "4";
            else if (s.length() == 7) number += "8";
            else if (s.length() == 5) number += std::to_string(i_use_five_segments_who_am_i(characters, numbers));
            else if (s.length() == 6) number += std::to_string(i_use_six_segments_who_am_i(characters, numbers));
        }
        if (!number.empty()) sum += std::stoi(number);
    }
    std::cout << sum << std::endl;
}