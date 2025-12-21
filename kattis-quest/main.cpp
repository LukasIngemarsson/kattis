#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int MAX_G = (int)1e5;

    int N;
    cin >> N;
    multiset<pair<int, int>> quests;
    for (int c = 0; c < N; ++c) {
        string S;
        cin >> S;
        if (S == "add") {
            int E, G;
            cin >> E >> G;
            quests.insert({E, G});
        }
        else {
            int X;
            cin >> X;
            long long ans = 0;
            while (X > 0) {
                auto it = quests.upper_bound({X, MAX_G});
                if (it == quests.begin())
                    break;
                --it;
                X -= it->first;
                ans += it->second;
                quests.erase(it);
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
