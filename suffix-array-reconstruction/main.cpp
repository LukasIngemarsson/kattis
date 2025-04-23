#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        int l, s; 
        cin >> l >> s;
        string str(l, '*');

        bool valid = true;
        while (s--) {
            int p;
            string suf;
            cin >> p >> suf;
            --p;
            
            int star_pos = -1;
            for (int i = p; i < l; ++i) {
                if (suf[i-p] == '*') {
                    star_pos = i - p;
                    break;
                }
                else if (str[i] == '*') {
                    str[i] = suf[i-p];
                }
                else if (str[i] != suf[i-p]) {
                    valid = false;
                    break;
                }
            }
            if (star_pos != -1) {
                for (int i = 1; i < suf.size() - star_pos; ++i) {
                    if (str[l-i] == '*') {
                        str[l-i] = suf[suf.size()-i];
                    }
                    else if (str[l-i] != suf[suf.size()-i]) {
                        valid = false;
                        break;
                    }
                }
            }
        }
        for (char& c : str) {
            if (c == '*') {
                valid = false;
                break;
            }
        }
        if (valid) {
            cout << str << '\n';
        }
        else {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}