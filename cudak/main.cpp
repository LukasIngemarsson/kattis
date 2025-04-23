#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define SINGLE_DIGITS 10
#define MAX_DIGITS 15
#define MAX_SUM 136

vector<ll> get_digs(ll num) {
    vector<ll> digits;
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    ll A, B, S;
    cin >> A >> B >> S;

    ll dp[MAX_DIGITS][MAX_SUM];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (ll i = 1; i < MAX_DIGITS; ++i) {
        for (ll j = 0; j <= MAX_SUM; ++j) {
            for (ll k = 0; k < SINGLE_DIGITS; ++k) {
                if (j + k >= MAX_SUM) break;
                dp[i][j + k] += dp[i - 1][j];
            }
        }
    }

    auto get_digsum_cnt = [&] (ll upper) -> ll {
        vector<ll> digits = get_digs(upper);
        ll num_digits = digits.size();
        ll dig, run_sum = 0, cnt = 0;

        for (ll i = 0; i < num_digits; ++i) {
            dig = digits[i];
            for (ll j = 0; j < dig; ++j) {
                if (run_sum + j > S) break;
                cnt += dp[num_digits - 1 - i][S - (run_sum + j)];
            }
            run_sum += dig;
            if (run_sum > S) break;
            if (i == num_digits - 1 && run_sum == S) {
                ++cnt;
            }
        }
        return cnt;
    };

    auto get_min_valid_num = [&] () {
        ll mid, low = A, high = B;
        while (low < high) {
            mid = (low + high) / 2;
            if (get_digsum_cnt(mid) - get_digsum_cnt(A - 1) > 0) {
                high = mid;
            }
            else {
                low = mid + 1;
            }
        }
        return low;
    };

    cout << get_digsum_cnt(B) - get_digsum_cnt(A - 1) << '\n';
    cout << get_min_valid_num() << '\n';

    return 0;
}