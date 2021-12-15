#include <bits/stdc++.h>

#ifdef aoc_test
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#define input_start _binary_test_txt_start
#define input_end _binary_test_txt_end
#else
#define input_start _binary_input_txt_start
#define input_end _binary_input_txt_end
#endif

extern "C" char input_start;
extern "C" char input_end;

void print_pairs(auto& pair_count) {
    for (const auto& pairs : pair_count) {
        if (pairs.second) {
            std::cout << pairs.first << " : " << pairs.second << std::endl;
        }
    }
}

void count_letters(auto& pair_count) {
    std::map<char, unsigned long> letter_count{};
    for (const auto& pairs : pair_count) {
        for (auto&c : pairs.first) {
            letter_count[c] += pairs.second;
        }
    }
    for (const auto& pairs : letter_count) {
        if (pairs.second) {
            std::cout << pairs.first << " : " << pairs.second << std::endl;
        }
    }
}

void solve() {
    const bool part1 = (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos);
    std::istringstream input(std::string(&input_start, &input_end - &input_start));

    std::string polymer_template;
    std::getline(input, polymer_template);
    std::map<std::string, unsigned long> pair_count{};
    std::map<std::string, float> letter_count{};

    for (auto &c : polymer_template) {
        std::string letter(1, c);
        letter_count[letter] += 1;
    }

    print_pairs(pair_count);

    std::map<std::string, std::tuple<std::string, std::string, std::string>> rules{};

    std::string line;
    while(std::getline(input, line)) {
        std::istringstream s(line);
        std::string first;
        std::getline(s, first, '-');
        std::string second;
        std::getline(s, second, '-');

        if (first.length() < 2 || second.length() < 1) continue;

        second.erase(0, 2);
        first.pop_back();

        pair_count[first] = 0ul;
        std::string output_left = first.at(0) + second;
        std::string output_right = second + first.at(1);

        rules[first] = std::tuple{output_left, output_right, second};
        std::cout << first << ":" << get<0>(rules[first]) << " & " << get<1>(rules[first]) << std::endl;
    }

    for (auto i = 0u; i < polymer_template.length() - 1; i++) {
        std::string pair = polymer_template.substr(i, 2);

        pair_count[get<0>(rules[pair])] += 1;
        pair_count[get<1>(rules[pair])] += 1;
        letter_count[get<2>(rules[pair])] += 1;
    }

        print_pairs(letter_count);
        print_pairs(pair_count);

    std::cout << "start" << std::endl;

    for (int u = 0; u < 10; u++) {
        auto step_count = pair_count;

        for (const auto& pairs : pair_count) {
            if (pairs.second) {
                std::cout << pairs.first << " appears " << pairs.second << " times gives " << get<0>(rules[pairs.first]) << " and " << get<1>(rules[pairs.first]) << " to " << get<2>(rules[pairs.first]) << std::endl;
                step_count[get<0>(rules[pairs.first])] += pairs.second;
                letter_count[get<2>(rules[pairs.first])] += pairs.second;
                //step_count[get<1>(rules[pairs.first])] += pairs.second;
            }
        }
        pair_count = step_count;
        print_pairs(letter_count);
        print_pairs(pair_count);
        std::cout << "===" << std::endl;
    }

   // count_letters(pair_count);

    std::cout << "===" << std::endl;
   
}

TEST(Test, TestAoc) {
  solve();
}

int main(int argc, char **argv) {
#ifdef aoc_test
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    solve();
#endif
}