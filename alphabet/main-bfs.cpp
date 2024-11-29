// too slow

#include <bits/stdc++.h>
using namespace std;

int bfs(string s) {
    queue<pair<int, int>> q;
    int n = s.size();
    vector<int> state(n, 1);
    for (int i = 0; i < n; ++i) {
        q.push({i, 1});
    }
    while (!q.empty()) {
        pair<int, int> p = q.front(); q.pop();
        if (state[p.first] > p.second) continue;
        state[p.first] = p.second;
        for (int i = p.first + 1; i < n; ++i) {
            if (s[i] <= s[p.first]) continue;
            q.push({i, p.second + 1});
        }
    }
    return *max_element(state.begin(), state.end());
}

int main() {
    std::cin.tie(0)->sync_with_stdio(false);

    string s;
    cin >> s;
    cout << 26 - bfs(s);

    return 0;
}