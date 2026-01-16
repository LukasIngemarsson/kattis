#include <bits/stdc++.h>
using namespace std;

pair<int, int> dirs[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

struct Solver {
    int H, W;
    vector<vector<int>> grid;
    vector<vector<pair<int, int>>> sinks;

    Solver(int H, int W) : H(H), W(W), 
                           grid(H, vector<int>(W)), 
                           sinks(H, vector<pair<int, int>>(W, {-1, -1})) {};

    bool in_bounds(int r, int c) {
        return r >= 0 && r < H && c >= 0 && c < W;
    }

    pair<int, int> dfs(int r, int c) {
        int minv = INT_MAX;
        int minr, minc;
        for (auto& d : dirs) {
            int nr = r + d.first, nc = c + d.second;
            if (!in_bounds(nr, nc)) {
                continue;
            }
            if (grid[nr][nc] < grid[r][c] && grid[nr][nc] < minv) {
                minv = grid[nr][nc];
                minr = nr, minc = nc;
            }
        }

        if (minv == INT_MAX) {
            sinks[r][c] = {r, c};
        }
        else if (sinks[minr][minc].first != -1) {
            sinks[r][c] = sinks[minr][minc]; 
        }
        else {
            sinks[r][c] = dfs(minr, minc);
        }
        return sinks[r][c];
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int H, W; cin >> H >> W;

        Solver s(H, W);
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cin >> s.grid[i][j];
            }
        }

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (s.sinks[i][j].first != -1) {
                    continue;
                }
                s.dfs(i, j);
            }
        }

        map<pair<int, int>, char> seen;
        cout << "Case #" << t << ":\n";
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                auto& crd = s.sinks[i][j];
                if (seen.find(crd) == seen.end()) {
                    seen[crd] = char(97 + seen.size());
                }
                cout << seen[crd];
                if (j < W - 1) cout << ' ';

            }
            cout << '\n';
        }
    }

    return 0;
}
