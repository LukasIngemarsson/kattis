// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

/*
@brief Suffix array. It sorts a provided string's suffixes 
in lexicographical order, storing the starting index of each 
suffix in the sorted array.

@note Time complexity (initialization): `O(n * log(n))`, where `n` 
is the length of the string.
@note Memory complexity: `O(n)`, where `n` is the length of the string.
*/
struct SuffixArray {
    /*
    The naive approach is to get all suffixes and sort them using quicksort or
    mergesort, while retaining their original indices. Sorting would on 
    average take `O(n * log(n))` time, and the comparison of two strings `O(n)` time,
    granting a total complexity of `O(n^2 * log(n))` (where `n` is the string length).

    The suffix array can be formed in `O(n * log(n))`. This is done by sorting suffixes
    by their prefixes iteratively, first with prefix length 1, then 2, 4, ..., up to `n`,
    where we can continously reuse the sorting results from previous iterations.

    A major benefit with the suffix array compared to the suffix trie/tree, is that it 
    does not save the suffixes themselves, but rather the index at which they begin
    in the original string, making it more memory efficient.
    */
    vector<int> arr;

    SuffixArray(string s) {
        // append string with arbitrary symbol that is lexicographically 
        // smaller than the all characters in the input data
        s += '\t'; // ascii value 9

        int n = s.size();
        const int alphabet = 256;

        /* Start by sorting suffixes only considering the first character of each suffix. */
        arr.resize(n);
        vector<int> c(n); // stores equivalence classes for suffix starting indices
        vector<int> cnt(max(alphabet, n));

        // count char frequencies
        for (int i = 0; i < n; ++i) {
            ++cnt[s[i]];
        }
        // calculate cumulative sum
        for (int i = 1; i < alphabet; ++i) {
            cnt[i] += cnt[i-1];
        }
        // populates the suffix array sorted by single-char prefixes
        for (int i = 0; i < n; ++i) {
            arr[--cnt[s[i]]] = i;
        }

        // assign initial class IDs to suffixes
        c[arr[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[arr[i]] != s[arr[i-1]]) ++classes;
            c[arr[i]] = classes - 1;
        }

        /* Iteratively sort suffixes, doubling prefix lengths after each iteration. 
        At each iteration, the class array `c` and suffix array `arr` contain the 
        results from the previous iteration, and temporary vectors are used to 
        store the results from the current iteration. */
        vector<int> tmp_arr(n), tmp_c(n);

        // in each iteration, sort suffixes based on their first `k` characters
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; ++i) {
                tmp_arr[i] = arr[i] - k; // shift
                if (tmp_arr[i] < 0) tmp_arr[i] += n; // wrap-around
            }

            fill(cnt.begin(), cnt.begin() + classes, 0);
            // count prefix frequencies
            for (int i = 0; i < n; ++i) {
                ++cnt[c[tmp_arr[i]]];
            }
            // calculate cumulative sum
            for (int i = 1; i < classes; ++i) {
                cnt[i] += cnt[i-1];
            }
            // insert suffixes into array sorted by prefix
            for (int i = n - 1; i >= 0; --i) {
                arr[--cnt[c[tmp_arr[i]]]] = tmp_arr[i];
            }

            // assign new class IDs for the new prefix length
            tmp_c[arr[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; ++i) {
                if (c[arr[i]] != c[arr[i-1]] || c[(arr[i] + k) % n] != c[(arr[i-1] + k) % n]) {
                    ++classes;
                }
                tmp_c[arr[i]] = classes - 1;
            }
            c.swap(tmp_c);
        }
        arr.erase(arr.begin()); // remove symbol
    }

    /* @brief Prints the suffix array. */
    void print() {
        cout << "suffix array: ";
        for (int a : arr) {
            cout << a << " ";
        }
        cout << '\n';
    }

    /*
    @brief Retrieves the starting index of the suffix ranked at the
    given index/rank in the suffix array.

    @param i: The index/rank of the suffix.

    @return The starting index of the suffix in the original string.

    @note Time complexity: `O(1)`.
    */
    int get_suffix(int i) {
        return arr[i];
    }
};

/*
@brief Kasai's algorithm. Computes the Longest Common Prefix (LCP) array
for the given string and its corresponding suffix array. The LCP array
will at each index `i` contain the LCP between the suffix at index `i`
and the subsequent index `i` + 1 in the suffix array.

@param s: The string.
@param suf_arr: The string's suffix array.

@return The LCP array.

@note Time complexity: `O(n)`, where `n` is the length of the string.
*/
vector<int> lcp(string s, SuffixArray suf_arr) {
    int n = s.size();
    vector<int> rank(n); // stores the rank/index of a suffix in the suffix array
    for (int i = 0; i < n; ++i) {
        rank[suf_arr.get_suffix(i)] = i;
    }

    /* Go through the suffix array and calculate the LCP between each
    pair of consecutive suffixes. */
    int k = 0;
    vector<int> lcp_arr(n - 1);
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suf_arr.get_suffix(rank[i] + 1);
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) {
            ++k;
        }
        lcp_arr[rank[i]] = k;
        if (k > 0) --k;
    }
    return lcp_arr;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int _; cin >> _;
    string s; cin >> s;
    SuffixArray suf_arr(s);
    auto lcp_arr = lcp(s, suf_arr);
    cout << *max_element(lcp_arr.begin(), lcp_arr.end()) << '\n';

    return 0;
}
