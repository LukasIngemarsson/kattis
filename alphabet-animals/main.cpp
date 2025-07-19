#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    string last_said;
    cin >> last_said;
    char last_char = last_said[last_said.size()-1];
    int n;
    cin >> n;
    vector<vector<string>> words(26);

    auto char_to_idx = [] (char ch) {
        return ch - 97;
    };

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        words[char_to_idx(s[0])].push_back(s);
    }    
    if (words[char_to_idx(last_char)].empty()) {
        cout << '?';
    }
    else {
        bool eliminate = false;
        for (string& w : words[char_to_idx(last_char)]) {
            if (words[char_to_idx(w[w.size()-1])].empty() || 
                w[w.size()-1] == last_char && words[char_to_idx(last_char)].size() == 1) {
                cout << w << '!'; 
                eliminate = true;
                break;
            }
        }
        if (!eliminate)
            cout << words[char_to_idx(last_char)][0];
    }
    return 0;
}