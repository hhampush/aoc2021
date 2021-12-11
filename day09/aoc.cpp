#include <bits/stdc++.h>
extern "C" char _binary_input_txt_start;
extern "C" char _binary_input_txt_end;

class point {
public:
    point() {}
    point(auto height) : height(height) {}
    point(auto* up, auto* down, auto* left, auto* right) : up(up), down(down), left(left), right(right) {}
    
    const point* up = nullptr;
    const point* down = nullptr;
    const point* left = nullptr;
    const point* right = nullptr;
    int height = 9;

    auto compare_nearby() const {
        auto up_height = (up != nullptr ? up->height : 9);
        auto down_height = (down != nullptr ? down->height : 9);
        auto left_height = (left != nullptr ? left->height : 9);
        auto right_height = (right != nullptr ? right->height : 9);
        return (height < up_height && height < down_height && height < left_height && height < right_height);
    }
};

inline void traverse(const point *p, auto &visited, auto &size) {
    if (p == nullptr || p->height == 9 || visited.contains(p)) return;
    visited.insert(p);
    size++;
    traverse(p->up, visited, size);
    traverse(p->down, visited, size);
    traverse(p->left, visited, size);
    traverse(p->right, visited, size);
}

int main(int argc, char **argv)
{
    const auto part1 = (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos);

    std::array<std::array<point, 100>, 100> map{};
    std::istringstream input(std::string(&_binary_input_txt_start, &_binary_input_txt_end - &_binary_input_txt_start));
    std::string line;
    int x = 0, y = 0;
    while (getline(input, line)) {
        for (auto& c : line) {
            map.at(y).at(x++) = point(c - '0');
        }
        y++;
        x = 0;
    }

    auto cmp = [](point* a, point* b) { return a->height > b->height; };
    std::priority_queue<point* , std::vector<point*>, decltype(cmp)> queue(cmp);

   for (auto y = 0u; y < map.size(); y++) {
       for (auto x = 0u; x < map.at(y).size(); x++) {
            auto* this_ptr = &(map.at(y).at(x));
            auto* up = (y == 0 ? nullptr : &(map.at(y-1).at(x)));
            auto* down = (y == (map.size() - 1) ? nullptr : &(map.at(y+1).at(x)));
            auto* left = (x == 0 ? nullptr : &(map.at(y).at(x-1)));
            auto* right = (x == (map.at(y).size() - 1) ? nullptr : &(map.at(y).at(x+1)));
            this_ptr->up = up;
            this_ptr->down = down;
            this_ptr->left = left;
            this_ptr->right = right;
            queue.push(this_ptr);
       }
   }

    std::unordered_set<const point*> visited{};
    std::vector<int> basins{};
    int sum = 0;
    while(!queue.empty()) {
        const point* p = queue.top();
        if (p->compare_nearby()) {
            sum += p->height + 1;
            if (!part1) {
                int size = 0;
                traverse(p, visited, size);
                basins.push_back(size);
            }
        }
        queue.pop();
    }
    if (!part1) {
        std::sort(basins.begin(), basins.end());
        int basin_product = 1;
        for (auto i = basins.size() - 1; i > basins.size() - 4; i--) {
            basin_product *= basins.at(i);
        }
        std::cout << basin_product << std::endl;
    } else {
        std::cout << sum << std::endl;
    }
}