#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bool>> has_box(n, vector<bool>(m));
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        has_box[x][y] = true;
    }
    int f, g;
    cin >> f >> g;

    queue<pair<int, int>> q;
    vector<vector<bool>> vis(n, vector<bool>(m));
    q.push({0, 0});
    vis[0][0] = true;
    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool valid = false;

    while(!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == f && c == g) {
            valid = true; 
            break;
        }

        for (auto& [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || has_box[nr][nc] || vis[nr][nc])
                continue;
            q.push({nr, nc});
            vis[nr][nc] = true;
        }
    }
    cout << (valid ? "SLEEPING" : "IMPOSSIBLE") << '\n';

    return 0;
}
