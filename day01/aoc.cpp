#include <bits/stdc++.h>
using namespace std;
int main() {
    int window_length = (getenv("part") == nullptr || string(getenv("part")).find("part1") == string::npos) ? 3 : 1, result = 0;
    for (auto [window_arr,file,line,i,prev_sum,curr_sum] = tuple{array<int,3>{0},ifstream("input.txt"), string(""), 0, INT_MAX, 0}; getline(file,line) && (window_arr.at(i++ % window_length) = stoi(line)); prev_sum = curr_sum) {
        result += ((curr_sum = (i >= window_length ? accumulate(begin(window_arr), begin(window_arr) + window_length, 0) : 0)) > prev_sum ? 1 : 0);
    };
    cout << result - (window_length > 1 ? 1 : 0);
}