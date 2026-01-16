#include <bits/stdc++.h>
using namespace std;

#define NUM_OUTCOMES 8
#define NUM_BITS 3

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        vector<vector<int>> prefs(m, vector<int>(NUM_OUTCOMES));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < NUM_OUTCOMES; ++j) {
                cin >> prefs[i][j];
            }
        }

        vector<vector<int>> state(m, vector<int>(NUM_OUTCOMES, -1));
        for (int i = m - 1; i >= 0; --i) {
                for (int b = 0; b < NUM_OUTCOMES; ++b) {
                    for (int j = 0; j < NUM_BITS; ++j) {
                        int idx = b ^ (1 << j);
                        int end_idx = (i == m - 1) ? idx : state[i+1][idx];
                        if (state[i][b] == -1 || prefs[i][end_idx] < prefs[i][state[i][b]]) {
                            state[i][b] = end_idx;
                        }
                    }
                }
        }

        for (int i = NUM_BITS - 1; i >= 0; --i) {
            cout << ((state[0][0] & (1 << i)) ? 'Y' : 'N');
        }
        cout << '\n';
    }

    return 0;
}