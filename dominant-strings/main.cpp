#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    const int A = 26;

    string s;
    vector<string> strs;
    while (cin >> s) strs.push_back(s);
    sort(strs.begin(), strs.end(), [] (const string& a, const string& b) {
        return a.size() < b.size();
    });

    vector<pair<int, vector<int>>> str_cnts;
    for (auto& s : strs) {
        vector<int> cnts(A);
        int bm = 0;
        for (char& c : s) {
            int i = c - 'a';
            ++cnts[i];
            bm |= 1 << i;
        }
        str_cnts.push_back({bm, cnts});
    }

    vector<string> dom_strs;
    int num_strs = strs.size();
    for (int i = 0; i < num_strs; ++i) {
        auto& pi = str_cnts[i];
        for (int j = i + 1; j < num_strs; ++j) {
            auto& pj = str_cnts[j];
            if ((pi.first & pj.first) != pi.first) continue;
            if (strs[i].size() >= strs[j].size()) continue;

            for (int k = 0; k < A; ++k) {
                if (pi.second[k] > pj.second[k]) goto next;
            }
            goto not_dominant;
            next:;
        }
        dom_strs.push_back(strs[i]);
        not_dominant:;
    }

    sort(dom_strs.begin(), dom_strs.end());
    for (auto& s : dom_strs) {
        cout << s << '\n';
    }

    return 0;
}
