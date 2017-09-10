// #include <iostream>
// #include <vector>

// using namespace std;

// #define max(a,b) (a>b?a:b)

// int optimal_weight(int W, const vector<int> &wt) {
//     int n = wt.size();
//     int ar[n + 1][W + 1];
//     for (int i = 0; i <= n; i++) {
//         for (int w = 0; w <= W; w++) {
//             if (i == 0 || w == 0) {
//                 ar[i][w] = 0;
//             } else if (wt[i - 1] <= w) {
//                 ar[i][w] = max(ar[i - 1][w], ar[i - 1][w - wt[i - 1]] + wt[i - 1]);
//             } else {
//                 ar[i][w] = ar[i - 1][w];
//             }
//         }
//     }
//     return ar[n][W];
// }

// int main() {
//     int n, W;
//     std::cin >> W >> n;
//     vector<int> w(n);
//     for (int i = 0; i < n; i++) {
//         std::cin >> w[i];
//     }
//     std::cout << optimal_weight(W, w) << '\n';
// }

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define pb push_back
#define mp make_pair
#define rep(i,n) for(i=0;i<n;i++)
#define repr(i,j,n) for(i=j;i<=n;i++)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vector<int> > graph;
const ll maxw = (ll) 1e4 + 1;
const ll maxn = (ll) 301;

//ll a[maxn];
ll dp[maxw][maxn];

ll solve(int wts[], int n, int in, int W) {
    if (W == 0 || in < 0) { return 0; }
    if (dp[W][in] >= 0) { return dp[W][in]; }
    ll w2 = solve(wts, n, in - 1, W);
    if (wts[in] > W) { return dp[W][in] = w2; }
    else { return dp[W][in] = MAX(solve(wts, n, in - 1, W - wts[in]) + wts[in], w2); }
}

int main() {
    std::ios::sync_with_stdio(0);
    ll i, j, k, t, q, m, l, r, n;
    int W;
    cin >> W >> n;
    int wt[n];
    rep(i, n) {
        cin >> wt[i];
    }

    rep(i, maxw) {
        rep(j, maxn) {
            dp[i][j] = -1;
        }
    }
    cout << solve(wt, n, n - 1, W) << endl;
}