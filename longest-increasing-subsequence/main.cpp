#include <bits/stdc++.h>
using namespace std;

/*
@brief Finds the longest increasing subsequence for a given sequence of numbers.

@param nums: The sequence of numbers.

@return A vector containing the indices of the elements in the longest increasing subsequence.

@note Time complexity: `O(nlog(n))`, where `n` is the number of elements in the total sequence.
*/
vector<int> lis(vector<int>& nums) { 
    // seq: stores the current ascending set of numbers
    // idxs: stores the index of the corresponding numbers in seq
    // parent: stores the index of the parent of a number/element
    vector<int> seq, idxs, parent(nums.size(), -1);

    // this for-loop is O(nlog(n)) as we perform a binary search for each element in the sequence
    for (int i = 0; i < nums.size(); ++i) {
        // binary search to find index of the first number currently in the sequence,
        // that is not less than the candidate number nums[i]
        int pos = lower_bound(seq.begin(), seq.end(), nums[i]) - seq.begin();
        if (pos == seq.size()) { // no number in the current sequence is >= the candidate num
            seq.push_back(nums[i]);
            idxs.push_back(i);
        }
        else {
            seq[pos] = nums[i];
            idxs[pos] = i;
        }
        if (pos > 0) {
            parent[i] = idxs[pos-1];
        }
    }

    vector<int> lis_idxs;
    for (int i = idxs.back(); i >= 0; i = parent[i]) {
        lis_idxs.push_back(i);
    }
    reverse(lis_idxs.begin(), lis_idxs.end());

    return lis_idxs;
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

    int n;
    while (cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }

        vector<int> ans = lis(nums);
        print_ans(ans);
    }

    return 0;
}
