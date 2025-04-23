#include <bits/stdc++.h>
using namespace std;

#define D 8
int grid[D][D];
pair<int, int> dirs[] = {{1, 2}, {-1, 2}, {2, 1}, {2, -1}};

struct Tr {
    int a, b, c;
    Tr(int a, int b, int c) : a(a), b(b), c(c) {}
};

bool oob(int r, int c) {
    return r < 0 || r >= D || c < 0 || c >= D;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        memset(grid, -1, sizeof(grid));
        char ch; cin >> ch;
        int c = ch - 'a';
        int r; cin >> r;
        r = 8 - r;

        queue<Tr> q;
        q.emplace(r, c, 0);

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int r = cur.a, c = cur.b, d = cur.c;
            for (auto& dir : dirs) {
                for (int f : {1, -1}) {
                    int nr = r + f * dir.first, nc = c + f * dir.second, nd = d + 1;
                    if (!oob(nr, nc) && (grid[nr][nc] == -1 || nd < grid[nr][nc])) {
                        grid[nr][nc] = nd;
                        q.emplace(nr, nc, nd);
                    }
                }
            }
        }

        int maxv = *max_element(&grid[0][0], &grid[0][0] + D * D);
        vector<string> ans;
        for (int r = 0; r < D; ++r) {
            for (int c = 0; c < D; ++c) {
                if (grid[r][c] == maxv) {
                    string s;
                    s.push_back(c + 'a');
                    s.push_back((8 - r) + '0');
                    ans.push_back(s);
                }
            }
        }
        cout << maxv << ' ';
        for (int i = 0; i < ans.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
