#include <bits/stdc++.h>
using namespace std; int main(int argc, char* argv[]) { const auto mod = (getenv("part") == nullptr || string(getenv("part")).find("part1") == string::npos) ? 3 : 1;
    for (auto [a,f,l,i,p,s] = tuple{array<int,3>{0},ifstream("input.txt"), string(""), 0, INT_MAX, 0}; getline(f,l) && (a.at(i++ % mod) = stoi(l)); p = s, cout << argc - (mod == 3 ? 2 : 0) << endl) {
        argc += ((s = (i >= 3 ? accumulate(begin(a), begin(a) + mod, 0) : 0)) > p ? 1 : 0); }; }