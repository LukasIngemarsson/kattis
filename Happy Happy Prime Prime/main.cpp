#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    auto is_prime = [] (int a) {
        if (a == 1) return false;

        for (int i = 2; i <= a / 2; ++i) {
            if (a % i == 0) return false;
        }
        return true;
    };

    int P; cin >> P;
    while (P--) {
        int K, m; cin >> K >> m;
        bool is_hp = true;
        if (!is_prime(m)) {
            is_hp = false;
        }
        else {
            unordered_set<int> seen;
            int a = m;
            while (true) {
                int sum = 0;
                while (a > 0) {
                    int dig = a % 10;
                    a /= 10;
                    sum += dig * dig;
                }
                if (sum == 1) {
                    break;
                }
                else if (seen.find(sum) != seen.end()) {
                    is_hp = false;
                    break;
                }
                seen.insert(sum);
                a = sum;
            }
        }
        cout << K << " " << m << " " << (is_hp ? "YES" : "NO") << '\n';
    }

    return 0;
}
