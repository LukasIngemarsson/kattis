// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

/*
@brief Finds each occurence of the given pattern in the given string, 
using the Knuth-Morris-Pratt algorithm.

@param s: The string.
@param p: The pattern.

@return A vector containing the start index of each occurence of the pattern.

@note Time complexity: `O(n + m)`, where `n` is the length of the pattern and
`m` is the length of the string.
*/
vector<int> find_pattern(string s, string p) {
    int n = p.size();

    /* Precalculate the prefix vector which will contain the index to resume 
    pattern-searching from if the pattern matches up to that character,
    but fails after. */
    vector<int> pfx(n);
    for (int i = 1; i < n; ++i) {
        int j = pfx[i-1];
        while (j > 0 && p[i] != p[j]) {
            j = pfx[j-1];
        }
        if (p[i] == p[j]) ++j;
        pfx[i] = j;
    }

    /* Search for pattern. */
    vector<int> matches; // stores the start index of matches
    int pos = 0; // index position in the pattern
    for (int i = 0; i < s.size(); ++i) {
        while (pos > 0 && p[pos] != s[i]) {
            pos = pfx[pos-1];
        }
        if (p[pos] == s[i]) ++pos;

        if (pos == n) {
            matches.push_back(i - (n - 1));
            pos = pfx[pos-1];
        }
    }

    return matches;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    string s, p;
    while (getline(cin, p) && getline(cin , s)) {
        auto matches = find_pattern(s, p);
        for (int i = 0; i < matches.size(); ++i) {
            if (i > 0) cout << " ";
            cout << matches[i];
        }
        cout << '\n';
    }

    return 0;
}