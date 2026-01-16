#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    long long N; cin >> N;

    long long a = N / 2 + 1;
    long long ans = a * (a + 1);
    if (N % 2 == 0) ans -= a;

    cout << ans << '\n';

    return 0;
}
