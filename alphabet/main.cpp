#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    string s;
    cin >> s;
    int n = s.size();
    vector<int> max_vals(n, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[i] < s[j]) {
                max_vals[j] = max(max_vals[i] + 1, max_vals[j]);
            }
        }
    }
    cout << 26 - *max_element(max_vals.begin(), max_vals.end());

    return 0;
}