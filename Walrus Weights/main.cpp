#include <bits/stdc++.h>
using namespace std;

int knapsack(int capacity, vector<int>& items) {
    int n = items.size();
    // dp table that stores the max combined value for placing 
    // i items (row) with a combined weight j (col)
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1));
    for (int i = 0; i <= n; ++i) {
        for (int maxw = 0; maxw <= capacity; ++maxw) {
            if (i == 0 || maxw == 0) { // no item/weight
                dp[i][maxw] = 0;
                continue;
            }
            int w = items[i-1];
            if (w <= maxw) {
                // set max value of choosing / not choosing the item
                dp[i][maxw] = max(w + dp[i-1][maxw-w], dp[i-1][maxw]);
            }
            else { // exceeds capacity, can't place item
                dp[i][maxw] = dp[i-1][maxw];
            }
        }
    }

    int opt = 0;
    for (int maxw = 0; maxw <= capacity; ++maxw) {
        if (abs(1000 - opt) >= abs(1000 - dp[n][maxw])) {
            opt = dp[n][maxw];
        }
    }
    return opt;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> items(n);
    for (int i = 0; i < n; ++i) {
        cin >> items[i];
    }
    int ans = knapsack(2000, items);
    cout << ans << '\n';


    return 0;
}