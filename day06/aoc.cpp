#include <bits/stdc++.h>
int main() {
    const int days = (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos) ? 80 : 256;
    std::array<unsigned long long, 9> fishtank{0};
    for (auto [file, token] = std::tuple{std::ifstream("input.txt"), std::string()}; std::getline(file, token, ',');) fishtank.at(std::stoi(token)) += 1;
    for (int i = 0; i < days; i++) {
        std::array<unsigned long long, 9> new_tank{0};
        for (auto f : {8, 7, 6, 5, 4, 3, 2, 1, 0}) {
            if (f != 0) new_tank.at(f - 1) = fishtank.at(f);
            else {
                new_tank.at(6) += fishtank.at(0);
                new_tank.at(8) += fishtank.at(0); }
        } fishtank = new_tank; }
    unsigned long total = std::accumulate(fishtank.begin(), fishtank.end(), total);
    std::cout << total << std::endl;
}