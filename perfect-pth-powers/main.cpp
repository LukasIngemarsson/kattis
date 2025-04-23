#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    ll x;
    while (cin >> x && x != 0) {
        ll ans = 1;
        for (ll i = -floor(sqrt(abs(x))); i <= floor(sqrt(abs(x))); ++i) {
            if ((i >= -1 && i <= 1) || x % i != 0) continue;

            ll val = i, p = 2;
            while (abs(val) <= abs(x / i)) {
                val *= i;
                if (val == x) {
                    ans = max(ans, p);
                }
                ++p;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}