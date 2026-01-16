#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;
    map<vector<int>, int> m;
    int max_freq = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> v(5);
        for (int j = 0; j < 5; ++j) {
            cin >> v[j];
        }
        sort(v.begin(), v.end());

        if (m.find(v) == m.end()) {
            m[v] = 1;
        }
        else {
            ++m[v];
        }
        max_freq = max(max_freq, m[v]);
    }
    int ans = 0;
    for (auto kvp : m) {
        if (kvp.second == max_freq) {
            ans += max_freq;
        }
    }
    cout << ans << '\n';

    return 0;
}
