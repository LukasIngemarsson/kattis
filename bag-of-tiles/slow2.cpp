#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int g; cin >> g;
    for (int gg = 1; gg <= g; ++gg) {
        int m; cin >> m;
        vector<int> tiles(m);
        for (int i = 0; i < m; ++i) cin >> tiles[i];
        int n, t; cin >> n >> t;

        int a = 0, b = 0;
        vector<int> idxs(n);
        for (int i = 0; i < n; ++i) idxs[i] = i;
        while (true) {
            int sum = 0;
            for (int i : idxs) sum += tiles[i];
            if (sum == t) ++a; else ++b;

            int bi = n - 1;
            while (bi >= 0 && idxs[bi] == m - n + bi) --bi;
            if (bi < 0) break;

            ++idxs[bi];
            for (int i = bi + 1; i < n; ++i) {
                idxs[i] = idxs[i - 1] + 1;
            }
        }

        cout << "Game " << gg << " -- " << a << " : " << b << '\n';
    }

    return 0;
}
