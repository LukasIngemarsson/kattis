#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct FenwickTree {
    int n; // tree size
    vector<ll> tree; // stores the tree values

    FenwickTree(int n) : n(n), tree(n + 1) {}

    // O(n) init
    FenwickTree(vector<ll> v) : n(v.size()), tree(v.size() + 1) {
        copy(v.begin(), v.end(), tree.begin() + 1); // 1-indexed
        for (int i = 1; i <= n; ++i) {
            int par = i + (i & -i);
            if (par <= n) {
                tree[par] += tree[i];
            }
        }
    }

    // adds a value to an element in the tree, 
    // and updates the other affected elements accordingly
    void add(int i, int d) { // O(log(n))
        // after each iteration, add the last set bit from i
        for (; i <= n; i += i & -i) { 
            tree[i] += d;
        }
    }

    // calculates the sum from 1 to the given index i (inclusive)
    ll sum(int i) { // O(log(n))
        ll sum = 0;
        // after each iteration, subtract the last set bit to i
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }

    // calculates the sum from i to j (inclusive)
    ll sum(int i, int j) {
        return sum(j) - sum(i - 1);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> idxs(N + 1); 
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        idxs[a] = i;
    }

    FenwickTree ft(vector<long long>(N, 1));
    int num = 1;
    for (int i = 1; i <= N; ++i) { 
        ft.add(idxs[num], -1);
        if (i % 2 != 0) {
            cout << ft.sum(idxs[num]) << '\n';
            num += N - i;
        }
        else {
            cout << ft.sum(idxs[num], N) << '\n';
            num -= N - i;
        }
    }

    return 0;
}