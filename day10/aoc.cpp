#include <bits/stdc++.h>
extern "C" char _binary_input_txt_start;
extern "C" char _binary_input_txt_end;

unsigned long long checkline(auto line, auto &err_parens, auto &err_square, auto &err_curly, auto &err_pointy, auto part1) {
    std::stack<int> round{};
    std::stack<int> curly{};
    std::stack<int> square{};
    std::stack<int> pointy{};
    std::stack<std::reference_wrapper<std::stack<int>>> order{};
    std::map<std::string, std::reference_wrapper<std::stack<int>>> stackmap_start{{"{", std::ref(curly)},
                                                                                  {"(", std::ref(round)},
                                                                                  {"[", std::ref(square)},
                                                                                  {"<", std::ref(pointy)}};
    std::map<std::string, std::reference_wrapper<std::stack<int>>> stackmap_end{{"}", std::ref(curly)},
                                                                                {")", std::ref(round)},
                                                                                {"]", std::ref(square)},
                                                                                {">", std::ref(pointy)}};
    std::map<std::string, std::reference_wrapper<int>> countermap{{"}", std::ref(err_curly)},
                                                                  {")", std::ref(err_parens)},
                                                                  {"]", std::ref(err_square)},
                                                                  {">", std::ref(err_pointy)}};
    std::stack<int> *toplevel = nullptr;
    int total_size = 0;
    for (auto &ch : line) {
        std::string c(1, ch);
        if (stackmap_start.count(c)) {
            auto &stack = stackmap_start.at(c).get();
            if (toplevel == nullptr) {
                toplevel = &stack;
            }
            stack.push(total_size++);
            order.push(stack);
        } else {
            auto &stack = stackmap_end.at(c).get();
            auto &counter = countermap.at(c).get();
            if (stack.empty() || stack.top() != total_size - 1) {
                counter++;
                return 0;
            }
            stack.pop();
            order.pop();
            total_size--;
            if (toplevel->empty() && (round.size() || curly.size() || square.size() || pointy.size())) {
                counter++;
                return 0;
            }
        }
    }

    if (part1) return 0;
    unsigned long long score = 0;
    if (!round.empty() || !curly.empty() || !square.empty() || pointy.empty()) {
        while (!order.empty()) {
            score *= 5;
            auto &stack = order.top().get();
            order.pop();
            if (&stack == &round)
                score += 1;
            else if (&stack == &curly)
                score += 3;
            else if (&stack == &square)
                score += 2;
            else if (&stack == &pointy)
                score += 4;
        }
    }

    return score;
}

int main(int argc, char **argv) {
    const auto part1 = (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos);
    std::istringstream input(std::string(&_binary_input_txt_start, &_binary_input_txt_end - &_binary_input_txt_start));

    int err_parens = 0;
    int err_square = 0;
    int err_curly = 0;
    int err_pointy = 0;
    std::vector<unsigned long long> scores{};
    std::string line;
    while (getline(input, line)) {
        const auto score = checkline(line, err_parens, err_square, err_curly, err_pointy, part1);
        if (score) scores.push_back(score);
    }

    if (part1) {
        const int error = err_parens * 3 + err_square * 57 + err_curly * 1197 + err_pointy * 25137;
        std::cout << error << std::endl;
        return 0;
    }

    std::sort(scores.begin(), scores.end());
    if (scores.size() > 0) {
        const unsigned long long median =
            (scores.size() % 2 == 0) ? (scores.at(scores.size() / 2) + scores.at(scores.size() / 2 - 1)) / 2.0 : scores.at(scores.size() / 2);
        std::cout << median << std::endl;
    }
}