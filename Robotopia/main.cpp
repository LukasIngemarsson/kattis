#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N;
    cin >> N;
    while (N--) {
        int l1, a1, l2, a2, lt, at;
        cin >> l1 >> a1 >> l2 >> a2 >> lt >> at;

        int sx = -1, sy = -1;
        bool valid = true;
        int xmax = lt / l1;
        for (int x = 1; x <= xmax; ++x) {
            int r = lt - l1 * x;
            if (r % l2 != 0)
                continue;
            int y = r / l2;
            if (a1 * x + a2 * y == at && y >= 1) {
                if (sx != -1 && sy != -1) {
                    valid = false;
                    break;
                }
                sx = x, sy = y;
            }
        }

        valid &= sx != -1 && sy != -1;
        if (!valid)
            cout << "?\n";
        else
            cout << sx << ' ' << sy << '\n';
    }

    return 0;
}
