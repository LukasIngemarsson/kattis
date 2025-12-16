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

    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    auto has_solution = [&](int max_depth) -> bool {
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        for (int r = 0; r < R; ++r) {
            if (grid[r][0] <= max_depth) {
                q.push({r, 0});
                visited[r][0] = true;
            }
        }
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            if (c == C - 1)
                return true;
            for (auto& [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                    continue;
                if (!visited[nr][nc] && grid[nr][nc] <= max_depth) {
                    q.push({nr, nc});
                    visited[nr][nc] = true;
                }
            }
        }
        return false;
    };

    int MAX_DEPTH = (int)1e7;
    int lo = 0, hi = MAX_DEPTH;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (has_solution(mid))
            hi = mid;
        else 
            lo = mid + 1;
    }
    int ans = lo;
    cout << ans << '\n';

    return 0;
}
