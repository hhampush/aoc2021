#include <bits/stdc++.h>

#ifdef aoc_test
#define input_start _binary_test_txt_start
#define input_end _binary_test_txt_end
#else
#define input_start _binary_input_txt_start
#define input_end _binary_input_txt_end
#endif

extern "C" char input_start;
extern "C" char input_end;

class octopus {
   public:
    octopus() {}
    octopus(int power, int x, int y) : power(power), x(x), y(y) {}
    int power;
    int x;
    int y;
    octopus* up;
    octopus* down;
    octopus* left;
    octopus* right;
    octopus* topleft;
    octopus* topright;
    octopus* bottomleft;
    octopus* bottomright;
    void explode(auto& exploded, auto& explosions);
    inline void step(auto& exploded, auto& explosions);
};

void octopus::explode(auto& exploded, auto& explosions) {
    if (exploded.contains(this)) {
        return;
    }
    power = 0;
    exploded.insert(this);
    explosions++;
    if (up != nullptr) up->step(exploded, explosions);
    if (down != nullptr) down->step(exploded, explosions);
    if (left != nullptr) left->step(exploded, explosions);
    if (right != nullptr) right->step(exploded, explosions);
    if (topleft != nullptr) topleft->step(exploded, explosions);
    if (topright != nullptr) topright->step(exploded, explosions);
    if (bottomleft != nullptr) bottomleft->step(exploded, explosions);
    if (bottomright != nullptr) bottomright->step(exploded, explosions);
}

inline void octopus::step(auto& exploded, auto& explosions) {
    if (power >= 9) explode(exploded, explosions);
    if (!exploded.contains(this)) power++;
}

void solve() {
    const bool part1 = (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos);
    std::istringstream input(std::string(&input_start, &input_end - &input_start));

    std::string line;
    std::array<std::array<octopus, 10>, 10> map{};
    int x = 0, y = 0;
    while (getline(input, line)) {
        for (auto& c : line) {
            map.at(y).at(x) = octopus(c - '0', x, y);
            x++;
        }
        y++;
        x = 0;
    }

    const int boundary = map.size() - 1;
    for (auto y = 0u; y < map.size(); y++) {
        for (auto x = 0u; x < map.at(y).size(); x++) {
            auto* this_ptr = &(map.at(y).at(x));
            auto* up = (y == 0 ? nullptr : &(map.at(y - 1).at(x)));
            auto* down = (y == boundary ? nullptr : &(map.at(y + 1).at(x)));
            auto* left = (x == 0 ? nullptr : &(map.at(y).at(x - 1)));
            auto* right = (x == boundary ? nullptr : &(map.at(y).at(x + 1)));

            auto* topleft = ((y == 0 || x == 0) ? nullptr : &(map.at(y - 1).at(x - 1)));
            auto* topright = ((y == 0 || x == boundary) ? nullptr : &(map.at(y - 1).at(x + 1)));
            auto* bottomleft = ((y == boundary || x == 0) ? nullptr : &(map.at(y + 1).at(x - 1)));
            auto* bottomright = ((y == boundary || x == boundary) ? nullptr : &(map.at(y + 1).at(x + 1)));
            this_ptr->up = up;
            this_ptr->down = down;
            this_ptr->left = left;
            this_ptr->right = right;
            this_ptr->topleft = topleft;
            this_ptr->topright = topright;
            this_ptr->bottomleft = bottomleft;
            this_ptr->bottomright = bottomright;
        }
    }

    std::unordered_set<const octopus*> exploded{};
    int explosions = 0;
    const int steps = (part1 ? 100 : 1000);
    for (int i = 0; i < steps; i++) {
        for (auto y = 0u; y < map.size(); y++) {
            for (auto x = 0u; x < map.at(y).size(); x++) {
                map.at(y).at(x).step(exploded, explosions);
            }
        }

        if (exploded.size() == 100) {
            std::cout << i << std::endl;
            return;
        }
        exploded.clear();
    }
    std::cout << explosions << std::endl;
}

int main(int argc, char** argv) { solve(); }
