#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    vector<pair<int, bool>> interval_pts;
    for (int i = 0; i < n; ++i) {
        int s, e;
        cin >> s >> e;
        interval_pts.push_back({s, false});
        interval_pts.push_back({e + k, true});
    } 
    sort(interval_pts.begin(), interval_pts.end());
    int cnt = 0, max_ = 0;
    for (auto& p: interval_pts) {
        if (!p.second) {
            ++cnt;
        }
        else {
            --cnt;
        }
        max_ = max(max_, cnt); 
    }
    cout << max_;

    return 0;
}