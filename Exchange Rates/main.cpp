#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    auto exch = [] (double x) -> double {
        return floor(100 * (0.97 * x)) / 100;
    };

    int d;
    while (cin >> d && d) {
        vector<double> rates(d);
        for (int i = 0; i < d; ++i) 
            cin >> rates[i];
        
        vector<pair<double, double>> dp(d + 1);
        dp[0].first = 1000;
        for (int i = 1; i <= d; ++i) {
            double r = rates[i-1];

            dp[i].first = max(dp[i-1].first, exch(dp[i-1].second * r));
            dp[i].second = max(dp[i-1].second, exch(dp[i-1].first / r));
        }

        cout << fixed << setprecision(2) << dp[d].first << '\n';
    }

    return 0;
}
