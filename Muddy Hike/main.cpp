#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int R, C;
    cin >> R >> C;
    vector<vector<int>> grid(R, vector<int>(C));
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            cin >> grid[r][c];
        }
    }

    int MAX_DEPTH = (int)1e7;
    vector<vector<int>> dp(R, vector<int>(C, MAX_DEPTH + 1));
    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    set<tuple<int, int, int>> q;
    for (int r = 0; r < R; ++r)
        q.insert({0, r, 0});
    while (!q.empty()) {
        auto [max_depth, r, c] = *q.begin(); 
        q.erase(q.begin());
        if (dp[r][c] <= max_depth)
            continue;
        dp[r][c] = max(max_depth, grid[r][c]);
        for (auto& [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;
            if (dp[r][c] <= dp[nr][nc])
                q.insert({dp[r][c], nr, nc});
        }
    }

    int ans = MAX_DEPTH;
    for (int r = 0; r < R; ++r)
        ans = min(ans, dp[r].back());
    cout << ans << '\n';

    return 0;
}
