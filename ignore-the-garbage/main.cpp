#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    vector<int> v = {0, 1, 2, 5, 9, 8, 6};
    ll K;
    while (cin >> K) {
        vector<ll> res;
        while (K > 0) {
            ll rem = K % 7;
            K /= 7;
            res.push_back(rem);
        }
        for (ll i : res) {
            cout << v[i];
        }
        cout << '\n';
    }

    return 0;
}