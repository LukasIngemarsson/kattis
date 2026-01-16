#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int X; cin >> X;
    int lim = floor(sqrt(X));
    int i = 2, k = 0;
    while (i <= lim) {
        if (X % i == 0) {
            X /= i;
            ++k;
        }
        else {
            ++i;
        }
    }
    if (X > lim) ++k;
    cout << k  << '\n';

    return 0;
}
