#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    while (cin >> n >> m) {
        vector<int> rmv(m);
        for (int i = 0; i < m; ++i) {
            cin >> rmv[i];
        }
        sort(rmv.begin(), rmv.end());

        vector<int> dp(n + 1);
        for (int i = 1; i <= n; ++i) {
            int nxt = 1; // next move is win or loss
            for (int j = 0; j < m && rmv[j] <= i; ++j) {
                nxt = min(nxt, dp[i - rmv[j]]);
            }
            dp[i] = 1 - nxt;
        }

        cout << (dp[n] == 1 ? "Stan" : "Ollie") << " wins" << '\n';
    }

    return 0;
}