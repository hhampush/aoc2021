#include <bits/stdc++.h>
int main() {
    auto [input, sorted, smallest] = std::tuple{std::vector<long>{}, std::vector<long>{}, std::pair<long, int>{INFINITY, 0}};
    for (auto [file, token] = std::tuple{std::ifstream("input.txt"), std::string()}; std::getline(file, token, ',');) {input.push_back(std::stoi(token));}
    
    sorted = input;
    std::sort(sorted.begin(), sorted.end());

    for (auto pos = 0; pos < sorted.at(sorted.size()-1); pos++) {
      long cost = 0;
      for (auto [crab_num, dist_to_pos] = std::tuple{0u, 0l}; crab_num < input.size(); crab_num++) {
        dist_to_pos = std::abs(input.at(crab_num) - pos);
        cost += (dist_to_pos*(dist_to_pos+1))/2;
      }
      if (cost < std::get<0>(smallest)) smallest = std::pair<long, int>{cost, pos};
    }
    std::cout << "smallest cost " << std::get<0>(smallest) << " at " << std::get<1>(smallest) << std::endl;
}
