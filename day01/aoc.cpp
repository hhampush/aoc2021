#include <bits/stdc++.h>
int main() {for (auto [f,l,p,c] = std::tuple{std::ifstream("input.txt"), std::string(""), 0, 0}; std::getline(f,l); c += (std::stoi(l) > p ? 1 : 0), p = std::stoi(l)) {std::cout << c << std::endl;}}
