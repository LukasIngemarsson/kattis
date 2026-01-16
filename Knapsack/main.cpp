#include <bits/stdc++.h>
using namespace std;

/*
@brief Finds the optimal way to fill a capacity limited knapsack, 
maximizing the total value for the packed items.

@param capacity: The capacity of the knapsack.
@param items: A vector of item (weight, value)-pairs.

@return A vector with the indices of the items present in the optimal solution.

@note Time complexity: `O(n * capacity)`, where `n` is the number of items.
*/
vector<int> knapsack(int capacity, vector<pair<int, int>>& items) {
    int n = items.size();
    // dp table that stores the max combined value for placing 
    // i items (row) with a combined weight j (col)
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1));

    // the nested for-loops below are O(n * capacity), as we fill the dp table
    for (int i = 0; i <= n; ++i) {
        for (int maxw = 0; maxw <= capacity; ++maxw) {
            if (i == 0 || maxw == 0) { // no item/weight
                dp[i][maxw] = 0;
                continue;
            }
            int v = items[i-1].first, w = items[i-1].second;
            if (w <= maxw) {
                // set max value of choosing / not choosing the item
                dp[i][maxw] = max(v + dp[i-1][maxw-w], dp[i-1][maxw]);
            }
            else { // exceeds capacity, can't place item
                dp[i][maxw] = dp[i-1][maxw];
            }
        }
    }

    vector<int> idxs;
    // the capacity variable is re-used here as "capacity remaining"
    for (int i = n; i > 0 && capacity > 0; --i) { 
        if (dp[i][capacity] != dp[i-1][capacity]) {
            idxs.push_back(i-1);
            capacity -= items[i-1].second;
        }
    }

    return idxs;
}

void print_ans(vector<int>& v) {
    cout << v.size() << '\n';
    for (int i = 0; i < v.size(); ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << v[i];
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int C, n;
    while (cin >> C >> n) {
        vector<pair<int, int>> items(n); // {value, weight} pairs
        for (int i = 0; i < n; ++i) {
            cin >> items[i].first >> items[i].second;
        }
        
        vector<int> ans = knapsack(C, items);
        print_ans(ans);
    }

    return 0;
}
