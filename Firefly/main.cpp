#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N, H; cin >> N >> H;
    vector<int> low, up;
    for (int i = 0; i < N; ++i) {
        int h; cin >> h;
        if (i % 2 == 0) low.push_back(h);
        else up.push_back(h);
    }

    sort(low.begin(), low.end());
    sort(up.begin(), up.end());

    int min_des = N, cnt = 0;
    for (int lvl = 1; lvl <= H; ++lvl) {
        int des = low.end() - lower_bound(low.begin(), low.end(), lvl);
        des += up.end() - lower_bound(up.begin(), up.end(), H - lvl + 1);
        if (des < min_des) {
            min_des = des;
            cnt = 1;
        }
        else if (des == min_des) ++cnt;
    }
    cout << min_des << " " << cnt << '\n';

    return 0;
}
