#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pi pair<int, int>
#define s second
#define f first

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int source, int target) {
    int n = adj.size();
    vector<long long> dist(n, INT_MAX);

    // min heap
    priority_queue < pi, vector<pi>, greater<pi> > pq;

    pq.push(mp(0, source));
    dist[source] = 0;

    while (!pq.empty()) {
        // get first vertex
        int u = pq.top().s;
        pq.pop();

        // going through all adjacent vertices of a vertex
        for (int i = 0; i < adj[u].size(); i++) {
            int w = adj[u][i];
            int weight = cost[u][i];

            // if there is a shirter path to w through u, update
            if (dist[w] > dist[u] + weight) {
                dist[w] = dist[u] + weight;
                pq.push(mp(dist[w], w));
            }
        }
    }

    return dist[target] == INT_MAX ? -1 : (int) dist[target];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
