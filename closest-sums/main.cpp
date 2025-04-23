#include <bits/stdc++.h>
using namespace std;

#define LONG_LONG_MAX 9223372036854775807LL

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, case_nr = 1;
    while (cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }
        int m;
        cin >> m;
        cout << "Case " << case_nr++ << ":\n";
        for (int i = 0; i < m; ++i) {
            int q;
            cin >> q;
            pair<long long, long long> opt = {LONG_LONG_MAX, LONG_LONG_MAX};
            for (int j = 0; j < n; ++j) {
                for (int k = j; k < n; ++k) {
                    if (j == k) {
                        continue;
                    }
                    long long sum = nums[j] + nums[k];
                    long long diff = abs(sum - q);
                    if (diff < opt.first) {
                        opt = {diff, sum};
                    }
                }
            }
            cout << "Closest sum to " << q << " is " << opt.second << ".\n";
        }
    }

    return 0;
}