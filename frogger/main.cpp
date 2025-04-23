#include <bits/stdc++.h>
using namespace std;

pair<int, int> dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0}};

struct Solver {
    int x, n, m, sr, sc, er, ec;
    vector<vector<string>> states; 
    vector<vector<vector<bool>>> vis; 

    Solver(vector<string>& grid, int x, int n, int m) : 
        x(x), n(n), m(m), states(m, vector<string>(n + 2)), vis(n + 2, vector<vector<bool>>(m, vector<bool>(m, false))) {
        sr = 0;
        er = n + 2 - 1;
        for (int i = 0; i < m; ++i) {
            if (grid[sr][i] == 'F')
                sc = i;
            if (grid[er][i] == 'G')
                ec = i;
        }
        states[0] = grid;
        for (int i = 1; i < m; ++i) {
            for (int r = 1; r <= n; ++r) {
                if (r % 2 != 0) {
                    rotate(grid[r].rbegin(), grid[r].rbegin() + 1, grid[r].rend());
                }
                else {
                    rotate(grid[r].begin(), grid[r].begin() + 1, grid[r].end());
                }
            }
            states[i] = grid;
        }

    }

    bool in_bounds(int r, int c) {
        return r >= 0 && r < n + 2 && c >= 0 && c < m;
    }

    int solve() { // bfs
        queue<tuple<int, int, int>> q;
        q.push({sr, sc, 0});
        vis[sr][sc][0] = true;

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int r = get<0>(cur), c = get<1>(cur), step = get<2>(cur);
            
            if (r == er && c == ec) {
                return step;
            }
            if (step >= x)
                continue;

            int state_idx = (step + 1) % m;
            vector<string>& state = states[state_idx];
            for (auto& d : dirs) {
                int nr = r + d.first, nc = c + d.second;
                if (in_bounds(nr, nc) && state[nr][nc] != 'X' && !vis[nr][nc][state_idx]) {
                    q.push({nr, nc, step + 1});
                    vis[nr][nc][state_idx] = true;
                }
            }
        }
        return -1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int x, n, m;
        cin >> x >> n >> m; cin.ignore();

        vector<string> grid(n + 2);
        for (int i = 0; i < n + 2; ++i) {
            getline(cin, grid[i]);
        }
        reverse(grid.begin(), grid.end());

        Solver solver(grid, x, n, m);

        int ans = solver.solve();
        if (ans == -1) {
            cout << "The problem has no solution.\n";
        }
        else {
            cout << "The minimum number of turns is " << ans << ".\n";
        }
    }

    return 0;
}
