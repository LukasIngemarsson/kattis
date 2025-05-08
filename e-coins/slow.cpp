#include <bits/stdc++.h>
using namespace std;

struct Solver {
    int m, S, ans;
    vector<pair<int, int>> coins;
    vector<vector<int>> mem;

    Solver (int m, int S) : m(m), S(S), ans(S + 1), coins(m), 
                            mem(S + 1, vector<int>(S + 1, 1e9)) {}

    double emod(int x, int y) {
        return sqrt(x * x + y * y);
    }

    void dfs(int x, int y, int step) {
        if (x > S || y > S) return;

        if (emod(x, y) == S) {
            ans = min(ans, step);
            return;
        }
        if (mem[x][y] <= step) return;

        mem[x][y] = step;
        for (const auto& [cx, cy] : coins) {
            dfs(x + cx, y + cy, step + 1);
        }
    }

    void solve() {
        dfs(0, 0, 0);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        int m, S; cin >> m >> S;
        Solver s(m, S);

        for (int i = 0; i < m; ++i) 
            cin >> s.coins[i].first >> s.coins[i].second;

        s.solve();
        if (s.ans == S + 1) {
            cout << "not possible\n";
        }
        else {
            cout << s.ans << '\n';
        }
    }

    return 0;
}
