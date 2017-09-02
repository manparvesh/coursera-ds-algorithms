#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
    //write your code here
    queue<int> q;
    int depth = 0;
    q.push(s);
    q.push(-1);
    std::vector<bool> visited(adj.size(), false);
    while (!q.empty()) {
        int top = q.front();
        q.pop();
        if (top == -1) {
            depth++;
            if (q.empty()) break;
            q.push(-1);
        } else {
            visited[top] = true;
            if (top == t) return depth;
            for (int i = 0; i < adj[top].size(); i++) {
                int w = adj[top][i];
                if (!visited[w]) {
                    q.push(w);
                }
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
