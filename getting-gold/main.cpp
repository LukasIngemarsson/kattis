#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int W, H;
    cin >> W >> H;
    vector<vector<char>> grid(H, vector<char>(W));
    pii start;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            cin >> grid[r][c];
            if (grid[r][c] == 'P') 
                start = {r, c};
        }
    }
    pii dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    queue<pii> q;
    q.push(start);
    grid[start.first][start.second] = '#';

    int ans = 0;
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        int r = cur.first, c = cur.second;

        bool trap = false;
        for (auto dr : dirs) {
            int nr = r + dr.first, nc = c + dr.second;
            if (grid[nr][nc] == 'T') {
                trap = true;
                break;
            }
        }
        if (trap)
            continue;

        for (auto dr : dirs) {
            int nr = r + dr.first, nc = c + dr.second;
            if (grid[nr][nc] == '#') 
                continue;

            if (grid[nr][nc] == 'G')
                ++ans;

            q.push({nr, nc});
            grid[nr][nc] = '#';
        }
    }
    cout << ans << '\n';

    return 0;
}
