#include <bits/stdc++.h>

std::tuple<long, int> p1(std::vector<long>& sorted) {
      long cost = 0, median = (sorted.size() % 2 == 0) ? (sorted.at(sorted.size()/2) + sorted.at(sorted.size()/2 - 1))/2.0 : sorted.at(sorted.size()/2);
      for (auto& pos : sorted) cost += std::abs(median - pos);
      return std::pair<long, int>{cost, median};
}

std::tuple<long, int> p2(std::vector<long>& sorted, std::vector<long>& input, std::pair<long, int> smallest = {INFINITY, 0}) {
    for (auto pos = 0; pos < sorted.at(sorted.size()-1); pos++) {
      long cost = 0;
      for (auto [crab_num, dist_to_pos] = std::tuple{0u, 0l}; crab_num < input.size(); crab_num++) {
        dist_to_pos = std::abs(input.at(crab_num) - pos);
        cost += (dist_to_pos*(dist_to_pos+1))/2;
      }
      if (cost < std::get<0>(smallest)) smallest = std::pair<long, int>{cost, pos};
    } return smallest;
}

int main() {
    auto [part1, input] = std::tuple{(getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos), std::vector<long>{}};
    for (auto [file, token] = std::tuple{std::ifstream("input.txt"), std::string()}; std::getline(file, token, ',');) {input.push_back(std::stoi(token));}
  
    std::vector<long> sorted = input;
    std::sort(sorted.begin(), sorted.end());

    auto smallest = (part1 ? p1(sorted) : p2(sorted, input));
    std::cout << "smallest cost " << std::get<0>(smallest) << " at " << std::get<1>(smallest) << std::endl;
}