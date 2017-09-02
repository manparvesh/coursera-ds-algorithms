#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

vector<bool> visited;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int i) {
    //write your code here
    visited[i] = true;
    for (int j = 0; j < adj[i].size(); j++) {
        int w = adj[i][j];
        if (!visited[w]) dfs(adj, used, order, w);
    }
    order.push_back(i);
}

vector<int> toposort(vector<vector<int> > adj) {
    vector<int> used(adj.size(), 0);
    vector<int> order;
    visited.resize(adj.size());
    //write your code here
    for (int i = 0; i < adj.size(); i++) {
        if (!visited[i]) {
            dfs(adj, used, order, i);
        }
    }
    return order;
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
    vector<int> order = toposort(adj);
    for (int i = order.size() - 1; i >= 0; i--) {
        cout << (order[i] + 1) << " ";
    }
}
