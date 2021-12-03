#include <bits/stdc++.h>
using namespace std;
int main() {
    int hor_pos = 0, depth = 0, aim = 0, part1 = (getenv("part") != nullptr && string(getenv("part")).find("part1") != string::npos);
    for (auto [f,l,i,up,down,forward] = tuple{ifstream("input.txt"), string(""), 0, false, false, false}; getline(f,l);) {
        for (auto [ss,sl,p] = tuple{stringstream(l), string(""), string("")}; getline(ss, sl, ' ');) {
            if (!(all_of(sl.begin(), sl.end(), ::isdigit) && (i = stoi(sl)))) {
                up = (sl.find("up") != string::npos), down = (sl.find("down") != string::npos), forward = (sl.find("forward") != string::npos);
            }
        }
        aim = aim + (up ? -i : down ? i : 0), hor_pos = hor_pos + (forward ? i : 0);
        depth = depth + (part1 ? (up ? -i : down ? i : 0) : (forward ? i * aim : 0));
    };
    cout << hor_pos * depth;
}