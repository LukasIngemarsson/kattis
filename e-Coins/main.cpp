#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        int m, S; cin >> m >> S;

        vector<pair<int, int>> coins(m);
        for (int i = 0; i < m; ++i) 
            cin >> coins[i].first >> coins[i].second;
        
        const int BND = S + 1;
        vector<vector<int>> dp(BND, vector<int>(BND, BND));
        dp[0][0] = 0;
        
        int ans = BND;
        for (int lvl = 0; lvl < BND; ++lvl) {
            if (2 * lvl * lvl > S * S) break;

            for (int r = lvl; r < BND; ++r) {
                for (const auto& [cc, cr] : coins) {
                    if (r - cr < 0 || lvl - cc < 0) continue;
                    dp[r][lvl] = min(dp[r][lvl], dp[r-cr][lvl-cc] + 1);
                }
                if (lvl * lvl + r * r == S * S) {
                    ans = min(ans, dp[r][lvl]);
                }
            }
            for (int c = lvl; c < BND; ++c) {
                for (const auto& [cc, cr] : coins) {
                    if (lvl - cr < 0 || c - cc < 0) continue;
                    dp[lvl][c] = min(dp[lvl][c], dp[lvl-cr][c-cc] + 1);
                }
                if (c * c + lvl * lvl == S * S) {
                    ans = min(ans, dp[lvl][c]);
                }
            }
        }

        if (ans == BND) {
            cout << "not possible\n";
        }
        else {
            cout << ans << '\n';
        }
    }

    return 0;
}
