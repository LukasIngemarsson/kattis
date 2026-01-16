#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; ++i)
        cin >> nums[i];

    vector<int> max_from_left(N), min_from_right(N);
    max_from_left[0] = nums[0];
    min_from_right.back() = nums.back();
    for (int i = 1; i < N - 1; ++i) {
        max_from_left[i] = max(max_from_left[i-1], nums[i]);
        int ri = N - 1 - i;
        min_from_right[ri] = min(min_from_right[ri+1], nums[ri]);
    }
    vector<int> pivot_vals;
    for (int i = 0; i < N; ++i) {
        bool ok_from_left = i == 0 || nums[i] >= max_from_left[i-1];
        bool ok_from_right = i == N - 1 || nums[i] <= min_from_right[i+1];
        if (ok_from_left && ok_from_right)
            pivot_vals.push_back(nums[i]);
    }

    int m = (int)pivot_vals.size();
    int LIMIT = 100;
    int upper = min(m, LIMIT);
    cout << m;
    for (int i = 0; i < upper; ++i)
        cout << ' ' << pivot_vals[i];
    cout << '\n';

    return 0;
}
