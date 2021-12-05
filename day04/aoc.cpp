#include <bits/stdc++.h>

bool is_winner(std::array<std::array<std::tuple<int, bool>, 5>, 5> &board, int x, int y, bool mode, bool winner = true) {
    for (int i = 0; i < 5; i++) if (get<1>(mode ? board.at(x).at(i) : board.at(i).at(y)) != true) winner = false;
    return winner; }

int unmarked_sum(std::array<std::array<std::tuple<int, bool>, 5>, 5> &board, int sum = 0) {
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++) if (get<1>(board.at(x).at(y)) != true) sum += get<0>(board.at(x).at(y));
    return sum; }

bool mark_in_board(std::vector<std::array<std::array<std::tuple<int, bool>, 5>, 5>> &boards, int num, int board, std::unordered_set<int> &winners)
{
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++) {
            if (!get<1>(boards.at(board).at(x).at(y)) && get<0>(boards.at(board).at(x).at(y)) == num) get<1>(boards.at(board).at(x).at(y)) = true;
            if (is_winner(boards.at(board), x, y, true) || is_winner(boards.at(board), x, y, false)) 
                return get<1>(winners.insert(board)); }
    return false; }

int main() {
    auto [boards, draw_pool, file, first_line, winners, output] = std::tuple{std::vector<std::array<std::array<std::tuple<int, bool>, 5>, 5>>(), std::vector<int>(), std::ifstream("input.txt"), std::string(""), std::unordered_set<int>(), std::string("")};
    getline(file, first_line);
    const auto view = first_line | std::ranges::views::split(',') | std::ranges::views::transform([]( auto &&str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); });
    for (auto &&word : view) draw_pool.push_back(std::atoi(word.data()));

    for (auto [line, board, x, y] = std::tuple{std::string(), std::array<std::array<std::tuple<int, bool>, 5>, 5>(), 0, 0}; !file.eof() && file >> line;) {
        board.at(x++).at(y) = {std::stoi(line), false};
        if (x == 5) {x = 0; y++;}; if (y == 5) {boards.push_back(board); x = 0, y = 0;}; }

    for (auto u = 0u; u < draw_pool.size(); u++) {
        for (auto [i, part1] = std::tuple{0u, (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos)}; i < boards.size(); i++)
            if (!winners.contains(i) && mark_in_board(boards, draw_pool.at(u), i, winners)) {
                output = std::string(std::to_string(unmarked_sum(boards.at(i)) * draw_pool.at(u)));
                if (part1) { return(std::printf("%s\n", output.c_str())); }}
    } std::cout << output << std::endl; }