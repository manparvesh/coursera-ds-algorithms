#include <bits/stdc++.h>
using namespace std;

bool *visited;

void dfs(vector<vector<int> > &adj, int s) {
    for (int i = 0; i < adj[s].size(); i++) {
        int w = adj[s][i];
        if (!visited[w]) {
            visited[w] = true;
            dfs(adj, w);
        }
    }
}

int number_of_components(vector<vector<int> > &adj) {
    int res = 0;
    visited = new bool[adj.size()];
    memset(visited, false, adj.size());
    //write your code here
    for (int i = 0; i < adj.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            res++;
            dfs(adj, i);
        }
    }
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
    std::cout << number_of_components(adj);
}
