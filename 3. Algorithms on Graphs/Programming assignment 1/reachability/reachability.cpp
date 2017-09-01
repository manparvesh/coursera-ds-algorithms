#include <bits/stdc++.h>
using namespace std;

bool *visited;

bool dfs(vector<vector<int> > &adj, int s, int y) {
    for (int i = 0; i < adj[s].size(); i++) {
        int w = adj[s][i];
        if (w == y) return true;
        if (!visited[w]) {
            visited[w] = true;
            return dfs(adj, w, y);
        }
    }
    return false;
}


int reach(vector<vector<int> > &adj, int x, int y) {
    int res = 0;
    if (x == y) return true;
    visited = new bool[adj.size()];
    memset(visited, false, adj.size());
    //write your code here
    res = dfs(adj, x, y);
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
}
