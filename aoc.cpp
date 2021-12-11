#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<array<char, 5>> rows({{0}});
    for (auto [col, file, line] = tuple{array<char, 5>({0}), ifstream("test.txt"), string("")}; getline(file, line);)
    {
        strncpy(col.data(), line.c_str(), 5);
        rows.push_back(col);
    }

    auto gamma = stringstream();
    auto epsilon = stringstream();
    for (int i = 0; i < 5; i++)
    {
        auto ss = stringstream();
        for (auto &r : rows)
        {
            ss << r.at(i);
        }

        auto s = ss.str();
        auto moar_1s = count(s.begin(), s.end(), '1') > count(s.begin(), s.end(), '0');
        gamma << (moar_1s ? '1' : '0');
        epsilon << (moar_1s ? '0' : '1');
    }
    cout << gamma.str() << endl
         << epsilon.str() << endl;
}