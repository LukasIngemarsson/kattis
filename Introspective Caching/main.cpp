#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int c, n, a;
    cin >> c >> n >> a;
    vector<int> accs(a);
    unordered_map<int, list<int>> idxs;
    for (int i = 0; i < a; ++i) {
        cin >> accs[i];
        idxs[accs[i]].push_back(i);
    }

    unordered_set<int> cache;
    set<pair<int, int>> next_idxs;
    int ans = 0;
    for (int i = 0; i < a; ++i) {
        idxs[accs[i]].pop_front();
        next_idxs.erase({i, accs[i]});
        
        if (cache.find(accs[i]) == cache.end()) {
            if (cache.size() >= c) {
                pair<int, int> last_next_idx = *next_idxs.rbegin();
                next_idxs.erase(last_next_idx);
                cache.erase(last_next_idx.second);
            }
            cache.insert(accs[i]);
            ++ans;
        }
        next_idxs.insert({(idxs[accs[i]].size() > 0) ? idxs[accs[i]].front() : a, accs[i]});
    }
    cout << ans << '\n';

    return 0;
}