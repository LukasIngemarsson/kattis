#include <bits/stdc++.h>
using namespace std;

struct Tr {
    int a, b, c;
    Tr(int a, int b, int c) : a(a), b(b), c(c) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int g; cin >> g;
    for (int gg = 1; gg <= g; ++gg) {
        int m; cin >> m;
        vector<int> tiles(m);
        for (int i = 0; i < m; ++i) cin >> tiles[i];
        int n, t; cin >> n >> t;

        queue<Tr> q; // (sum, index in tiles)
        q.emplace(0, 0, 0);

        int a = 0, b = 0; 
        while(!q.empty()) {
            auto [sum, idx, num_chosen] = q.front(); q.pop();

            if (num_chosen == n) {
                if (sum == t) ++a; 
                else ++b;
                continue;
            }

            if (sum > t || idx >= m || m - idx + num_chosen < n) continue;

            q.emplace(sum + tiles[idx], idx + 1, num_chosen + 1);
            q.emplace(sum, idx + 1, num_chosen);
        }

        cout << "Game " << gg << " -- " << a << " : " << b << '\n';
    }

    return 0;
}
