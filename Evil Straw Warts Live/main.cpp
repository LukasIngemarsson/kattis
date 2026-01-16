#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int slen = s.size();

        unordered_map<char, int> counts;        
        for (char& c : s) {
            ++counts[c];
        }

        bool ok = true, one_odd = false;
        for (auto& kvp : counts) {
            if (kvp.second % 2 != 0) {
                if (slen % 2 == 0 || one_odd) {
                    ok = false;
                    break;
                }
                one_odd = true;
            }
        }
        if (!ok) {
            cout << "Impossible\n";
            continue;
        }
        int swaps = 0;
        for (int i = 0; i < slen / 2; ++i) {
            char c = s[i];
            if (counts[c] > 1) {
                int last_idx = -1;
                for (int j = slen - i - 1; j > i; --j) {
                    if (s[j] == c) {
                        last_idx = j;
                        break;
                    }
                }
                assert(last_idx != -1);
                for (int j = last_idx + 1; j < slen - i; ++j) {
                    swap(s[j], s[j-1]);
                    ++swaps;
                }
                counts[c] -= 2;
            }
            else {
                swaps += slen / 2 - i;
                s.erase(s.begin() + i);
                --i;
                --slen;
                --counts[c];
            }
        }
        cout << swaps << '\n';
    }

    return 0;
}
