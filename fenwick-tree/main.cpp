// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
@brief For a given vector of numbers, the Fenwick Tree allows for efficient prefix sum queries and updates.

@note Memory complexity: `O(n)`, where `n` is the number of elements.
@note Uses 1-based indexing.
*/
struct FenwickTree {
    /*
    The naive approach for prefix sums is simply to iterate through the array and add up the number one by one, 
    which takes `O(n)` time. The Fenwick Tree improves this by maintaining cumulative subrange sums for the
    the array, using binary representations for the indices to effectively construct the total desired sum.
    Similarily, the tree can use the binary index representations to propogate the update of an element 
    to the affected subrange sums in the tree.

    For every (2^1) 2nd index, we maintain a sum of (2^0) a single element.
    For every (2^2) 4th index, we maintain a sum of (2^1) 2 consecutive elements.
    For every (2^3) 8th index, we maintain a sum of (2^2) 4 consecutive elements, 
    and so on.

    Example for intuition:
    Let's say we have the following array: 
    [1, 2, 3, 4, 5, 6, 7],

    then we would get the following tree array:
    [1, 3, 3, 10, 5, 11, 7],
    
    which as the name suggests can be visualized as a tree:
              10
        3            11
    1      3      5      7

    For the query 7, assuming 1-based indexing, we would compute the sum as:
    sum(7) = tree[7] + tree[6] + tree[4] = 7 + 11 + 10 = 28.
    */
   
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

    /*
    @brief Adds a value to an element in the tree, and updates the tree accordingly.

    @param i: The index of the element.
    @param d: The value to be added to the element.

    @note Time complexity: `O(log(n)`, where `n` is the number of elements in the tree.
    */
    void add(int i, int d) { 
        // after each iteration, add the last set bit to i
        for (; i <= n; i += i & -i) { 
            tree[i] += d;
        }
    }

    /*
    @brief Calculates the prefix sum from 1 up to the given upper-bound index `i` (inclusive).

    @param i: The index of the upper bound.

    @return The prefix sum.

    @note Time complexity: `O(log(n))`, where `n` is the number of elements in the tree.
    */
    ll sum(int i) {
        ll sum = 0;
        // after each iteration, subtract the last set bit from i
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }

    /*
    @brief Calculates the sum from the lower-bound index `i` to the given upper-bound index `j` (inclusive).

    @param i: The index of the lower bound.
    @param j: The index of the upper bound.

    @return The desired range sum.

    @note Time complexity: `O(log(n))`, where `n` is the number of elements in the tree.
    */
    ll sum(int i, int j) {
        return sum(j) - sum(i - 1);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;

    char ch;
    int i, d;
    FenwickTree ft(N);
    for (int _ = 0; _ < Q; ++_) {
        cin >> ch >> i;
        if (ch == '+') {
            cin >> d;
            ft.add(i + 1, d);
        }
        else if (ch == '?') {
            cout << ft.sum(i) << '\n';
        }
    }

    return 0;
}