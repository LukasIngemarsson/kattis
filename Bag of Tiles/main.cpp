#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int g; cin >> g;
    for (int gg = 1; gg <= g; ++gg) {
        int m; cin >> m;
        vector<int> tiles(m);
        for (int i = 0; i < m; ++i) cin >> tiles[i];
        int n, t; cin >> n >> t;

        vvvi dp(m + 1, vvi(n + 1, vi(t + 2)));
        dp[0][0][0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j <= min(i, n); ++j) {
                for (int s = 0; s <= t + 1; ++s) {
                    dp[i][j][s] += dp[i-1][j][s];
                    if (j >= n) continue;

                    // t + 1 used as oob cnt
                    dp[i][j+1][min(s+tiles[i-1], t+1)] += dp[i-1][j][s];

                }
            }
        }

        int a = dp[m][n][t];
        int b = dp[m][n][t+1];
        for (int s = 0; s < t; ++s) b += dp[m][n][s];
        cout << "Game " << gg << " -- " << a << " : " << b << '\n';
    }

    return 0;
}
