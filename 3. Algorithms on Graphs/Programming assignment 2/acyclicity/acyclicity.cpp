#include <iostream>
#include <vector>

using namespace std;

vector<bool> visited, rec_stack;

bool _acyclic(vector<vector<int> > &adj, int i) {
    if (!visited[i]) {
        // put in recursive stack and mark visited
        visited[i] = true;
        rec_stack[i] = true;

        for (int j = 0; j < adj[i].size(); j++) {
            int w = adj[i][j];
            if (!visited[w] && _acyclic(adj, w)) {
                return true;
            } else if (rec_stack[w]) {
                return true;
            }
        }
    }
    // remove this element from recursive stack and return false
    rec_stack[i] = false;
    return false;
}

bool acyclic(vector<vector<int> > &adj) {
    visited.resize(adj.size());
    rec_stack.resize(adj.size());

    for (int i = 0; i < adj.size(); i++) {
        if (_acyclic(adj, i)) return true;
    }

    return false;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj);
}
