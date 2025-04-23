#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N, L, W;
    cin >> N >> L >> W;
    vector<double> tree_pos(N);
    for (int i = 0; i < N; ++i) {
       cin >> tree_pos[i]; 
    }
    sort(tree_pos.begin(), tree_pos.end());

    vector<double> slot_pos;
    for (int i = 0; i < N / 2; ++i) {
        slot_pos.push_back(i * (L / (N / 2 - 1.0)));
    }

    vector<vector<double>> dp(N / 2 + 1, vector<double>(N / 2 + 1, numeric_limits<double>::max()));
    dp[0][0] = 0.0;
    for (int i = 1; i <= N / 2; ++i) {
        dp[i][0] = dp[i-1][0] + abs(tree_pos[i-1] - slot_pos[i-1]); 
        dp[0][i] = dp[0][i-1] + sqrt(pow(tree_pos[i-1] - slot_pos[i-1], 2) + pow(W, 2));
    }
    for (int i = 1; i <= N / 2; ++i) {
        for (int j = 1; j <= N / 2; ++j) {
            dp[i][j] = min(dp[i-1][j] + abs(tree_pos[i+j-1] - slot_pos[i-1]),
                            dp[i][j-1] + sqrt(pow(tree_pos[i+j-1] - slot_pos[j-1], 2) + pow(W, 2)));
        }
    }
    cout << fixed << setprecision(10) << dp[N/2][N/2] << '\n';

    return 0;
}