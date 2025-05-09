#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    vector<string> grid;
    string s;
    while (getline(cin, s))
        grid.push_back(s);

    const int N = 8;

    auto oob = [] (int r, int c) -> bool {
        return r < 0 || r >= N || c < 0 || c >= N;
    };

    auto is_valid = [&] () -> bool {
        int cnt = 0;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (grid[r][c] == '*') ++cnt;
            }
        }
        if (cnt != 8) return false;

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (grid[r][c] == '*') {
                    for (int dr = -1; dr <= 1; ++dr) {
                        for (int dc = -1; dc <= 1; ++dc) {
                            if (dr == 0 && dc == 0) continue;
                            
                            for (int i = 1; !oob(r + i * dr, c + i * dc); ++i) {
                                if (grid[r+i*dr][c+i*dr] == '*') return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    };

    cout << (is_valid() ? "" : "in") << "valid\n";

    return 0;
}
