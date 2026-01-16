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
    // precalculate the prefix vector which will contain the index to resume 
    // pattern-searching from if the pattern matches up to that character,
    // but fails after
    vector<int> pfx(n);
    for (int i = 1; i < n; ++i) {
        int j = pfx[i-1];
        while (j > 0 && p[i] != p[j]) {
            j = pfx[j-1];
        }
        if (p[i] == p[j]) ++j;
        pfx[i] = j;
    }

    // search for pattern
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

    string s;
    vector<string> dict;
    while (getline(cin, s) && s != "#") dict.push_back(s);

    string m = "";
    while (getline(cin, s) && s != "#") {
        m += s;
        if (m.back() == '|') {
            m.pop_back();
            
            vector<pair<int, int>> matches;
            for (auto& d : dict) {
                auto match = find_pattern(m, d);
                for (int i : match) {
                    matches.push_back({i, i + d.size() - 1});
                }
            }

            sort(matches.begin(), matches.end(), [] (const pair<int, int>& a, const pair<int, int>& b) {
                if (a.second == b.second) return a.first < b.first;
                return a.second < b.second;
            });

            int cnt = 0;
            int cur_end = -1;
            for (int i = 0; i < matches.size(); ++i) {
                if (matches[i].first > cur_end) {
                    cur_end = matches[i].second;
                    ++cnt;
                }
            }
            cout << cnt << '\n';
            m = "";
        }
    }

    return 0;
}
