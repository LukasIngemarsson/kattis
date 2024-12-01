#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    } 
    sort(heights.begin(), heights.end());
    int min_area = INT_MAX;
    for (int k = 0; k <= n / 2; ++k) {
        int h_max = heights.back();
        for (int i = 0; i < k; ++i) {
            h_max = max(h_max, heights[i] + heights[2*k-i-1]);
        }
        min_area = min(min_area, h_max * (n - k) * 66);
    }
    cout << min_area;

    return 0;
}