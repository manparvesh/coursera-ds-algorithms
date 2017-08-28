#include <iostream>
#include <vector>

using std::vector;
#define max(a,b) (a>b?a:b)

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    int dp[102][102][102] = {0};
    int la = a.size(), lb = b.size(), lc = c.size();
    for (int i = 1; i <= la; i++) {
        for (int j = 1; j <= lb; j++) {
            for (int k = 1; k <= lc; k++) {
                if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
                    dp[i][j][k] = 1 + dp[i - 1][j - 1][k - 1];
                } else {
                    dp[i][j][k] = max(dp[i - 1][j][k], max(dp[i][j - 1][k], dp[i][j][k - 1]));
                }
            }
        }
    }
    return dp[la][lb][lc];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
