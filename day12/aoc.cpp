#include <bits/stdc++.h>
#define input_start _binary_input_txt_start
#define input_end _binary_input_txt_end

extern "C" char input_start;
extern "C" char input_end;

class node {
    public:
        node() = default;
        node(std::string id, bool chunky_cave) : id(id), chunky_cave(chunky_cave) {}
        std::string id;
        bool chunky_cave;
        std::vector<node*> edges;
};

void search(auto visited, auto visited_once, auto* allowed_twice, auto& visited_order, auto& node_map, auto* node, auto& paths, auto& full_paths) {
    visited.insert(node);

    if (node->id.compare("end") == 0) {
        paths++;
        std::string path("");
        for (auto& n : visited_order) {
            path += n->id + ",";
        }
        path += node->id + "\n";
        full_paths.insert(path);
        return;
    }

    for (auto & edge : node->edges) {
        if (!visited.contains(edge) || edge->chunky_cave) {
            visited_order.push_back(node);
            search(visited, visited_once, allowed_twice, visited_order, node_map, edge, paths, full_paths);
            visited_order.pop_back();
        } else if (edge == allowed_twice && !visited_once) {
            visited_order.push_back(node);
            search(visited, true, allowed_twice, visited_order, node_map, edge, paths, full_paths);
            visited_order.pop_back();
        }
    }
}

void solve() {
    const bool part1 = (getenv("part") != nullptr && std::string(getenv("part")).find("part1") != std::string::npos);
    std::istringstream input(std::string(&input_start, &input_end - &input_start));

    std::map<std::string, node> node_map{};

    std::string line("");
    int big_caves = 0;
    while (std::getline(input, line)) {
        std::istringstream s(line);

        std::string first_token("");
        std::getline(s, first_token, '-');

        if (!node_map.count(first_token)) {
            const bool is_chunky = std::isupper(first_token.at(0));
            if (is_chunky) big_caves++;
            node_map[first_token] = node(first_token, is_chunky);
        }

        std::string second_token("");
        std::getline(s, second_token, '-');

        if (!node_map.count(second_token)) {
            const bool is_chunky = std::isupper(second_token.at(0));
            if (is_chunky) big_caves++;
            node_map[second_token] = node(second_token, std::isupper(second_token.at(0)));
        }

        node_map[first_token].edges.push_back(&node_map[second_token]);
        node_map[second_token].edges.push_back(&node_map[first_token]);
    }

    node* start = &node_map["start"];
    int paths = 0;
    std::unordered_set<std::string> full_paths{};

    if (part1) {
        std::vector<node*> visited_order{};
        std::set<node*> visited{};
        search(visited, true, start, visited_order, node_map, start, paths, full_paths);
        std::cout << paths << std::endl;
    }
    else {
        for (const auto& node_pair : node_map) {
            if (node_pair.first.compare("start") != 0 && node_pair.first.compare("end") && !node_pair.second.chunky_cave) {
                std::vector<node*> visited_order{};
                std::set<node*> visited{};
                bool visited_once = false;
                search(visited, visited_once, &node_pair.second, visited_order, node_map, start, paths, full_paths);
            }
        }
        std::cout << full_paths.size() << std::endl;
    }
}

int main(int argc, char **argv) {
    solve();
}