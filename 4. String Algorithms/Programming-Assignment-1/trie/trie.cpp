#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
    trie t;
    int counter = 0;
    edges e;
    t.push_back(e);

    for (string pattern : patterns) {
        int current_node = 0;
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            edges edge = t[current_node];
            if (edge.find(c) != edge.end()) {
                current_node = edge[c];
            } else {
                counter++;
                edge[c] = counter;
                current_node = counter;
            }
        }
        t.push_back(edge);
    }

    return t;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<string> patterns;
    for (size_t i = 0; i < n; i++) {
        string s;
        std::cin >> s;
        patterns.push_back(s);
    }

    trie t = build_trie(patterns);
    for (size_t i = 0; i < t.size(); ++i) {
        for (const auto & j : t[i]) {
            std::cout << i << "->" << j.second << ":" << j.first << "\n";
        }
    }

    return 0;
}