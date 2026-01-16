#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    ll d, n, m;
    cin >> d;
    while (d--) {
        cin >> n >> m;
        vector<ll> v(n);
        for (ll i = 0; i < n; ++i) {
            cin >> v[i];
        }

        ll sum = 0, opt = 0, last_m_sum = 0;
        bool m_in_seq = false;
        for (ll i = 0; i < n; ++i) {
            if (v[i] > m) {
                sum += v[i];
            }
            else if (v[i] == m) {
                sum = sum - last_m_sum + m;
                last_m_sum = sum;
                m_in_seq = true;
            }
            else {
                sum = 0;
                last_m_sum = 0;
                m_in_seq = false;
            }
            if (m_in_seq) {
                opt = max(opt, sum);
            }
        }
        cout << opt << '\n';
    }

    return 0;
}
