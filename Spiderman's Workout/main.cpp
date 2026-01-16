#include <bits/stdc++.h>
using namespace std;

int N, M;
pair<int, string> ans = {INT_MAX, ""};
vector<unordered_map<int, int>> state(40);

void dfs(vector<int>& v, int i=0, int h=0, string path="", int curr_max_h=0) {
    if (i >= M) {
        if (h == 0) {
            ans.first = curr_max_h;
            ans.second = path;
        }
        return;
    }
    if (h < 0 || curr_max_h >= ans.first || (state[i].find(h) != state[i].end() && curr_max_h >= state[i][h])) {
        return;
    }
    state[i][h] = curr_max_h;
    dfs(v, i + 1, h + v[i], path + "U", max(curr_max_h, h + v[i]));
    dfs(v, i + 1, h - v[i], path + "D", curr_max_h);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    cin >> N;
    for (int _ = 0; _ < N; ++_) {
        cin >> M;
        vector<int> v(M);
        for (int i = 0; i < M; ++i) {
            cin >> v[i];
        }
        dfs(v);
        cout << ((ans.first < INT_MAX) ? ans.second : "IMPOSSIBLE") << '\n';
        ans = {INT_MAX, ""};
        state.assign(40, unordered_map<int, int>());
    }

    return 0;
}