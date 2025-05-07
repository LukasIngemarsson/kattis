#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        int a, b, p, q; 
        cin >> a >> b >> p >> q;
        int c, d, r, s;
        cin >> c >> d >> r >> s;
        int v = (a - b - c + d) % gcd(gcd(gcd(p, q), r), s);
        cout << ((v == 0) ? "Yes" : "No") << '\n';
    }

    return 0;
}
