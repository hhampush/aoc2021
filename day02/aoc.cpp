#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[], char *envp[]) {
    int hor_pos = 0, depth = 0, aim = 0;
    const auto part1 = (getenv("part") == nullptr || string(getenv("part")).find("part1") == string::npos) ? false : true;
    for (auto [f,l,i,k] = tuple{ifstream("input.txt"), string(""), 0, string("")}; getline(f,l);) {
        for (auto [ss,sl,p] = tuple{stringstream(l), string(""), string("")}; getline(ss, sl, ' ');) {try{ i = stoi(sl); } catch (exception& e){k = sl;}}
        aim += (k.find("up") != string::npos ? -i : (k.find("down") != string::npos ? i : 0)); hor_pos += (k.find("forward") != string::npos ? i : 0);
        if (!part1) depth += (k.find("forward") != string::npos ? i * aim : 0); else depth += (k.find("up") != string::npos ? -i : (k.find("down") != string::npos ? i : 0));
    };
    cout << hor_pos * depth;
 }
