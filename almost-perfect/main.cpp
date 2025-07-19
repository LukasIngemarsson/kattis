#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n) {
        int sum = 1; 
        for (int i = 2; i <= floor(sqrt(n)); ++i) {
            if (n % i == 0) {
                sum += i;
                if (i != n / i) {
                    sum += n / i; 
                }
            }
        }
        cout << n << " ";
        if (sum == n) {
            cout << "perfect";
        }
        else if (abs(n - sum) <= 2) {
            cout << "almost perfect";
        }
        else {
            cout << "not perfect";
        }
        cout << '\n';
    }

    return 0;
}