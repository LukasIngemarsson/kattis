#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cin.tie(0)->sync_with_stdio(false);

    int n, x;
    cin >> n >> x;
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    } 
    sort(prices.begin(), prices.end());
    if (n == 1)
        cout << 1;
    for (int i = 1; i < n; ++i) {
        if (prices[i] + prices[i-1] > x) {
            cout << i;
            break;
        }
        if (i == n - 1)
            cout << i + 1;
    }

    return 0;
}