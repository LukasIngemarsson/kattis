#include <bits/stdc++.h>
using namespace std;

struct double_ended_map {
    unordered_map<string, int> str_to_int;
    unordered_map<int, string> int_to_str;

    const int& operator[] (const string& s) const {
        return str_to_int.at(s);
    }
    
    const string& operator[] (int i) const {
        return int_to_str.at(i);
    }

    void insert(const string& s, int i) {
        str_to_int[s] = i;
        int_to_str[i] = s;
    }

    void erase(int i) {
        string s = int_to_str[i];
        int_to_str.erase(i);
        str_to_int.erase(s);
    }

    bool contains_str(string s) {
        return str_to_int.find(s) != str_to_int.end();
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, cnt = 0;
    cin >> n;
    double_ended_map events;
    for (int _ = 0; _ < n; ++_) {
        char cmd;
        cin >> cmd;
        if (cmd == 'E') {
            string s;
            cin >> s;
            events.insert(s, ++cnt);
        }
        else if (cmd == 'D') {
            int r;
            cin >> r;
            for (int i = 0; i < r; ++i) {
                events.erase(cnt - i);
            }
            cnt -= r;
        }
        else if (cmd == 'S') {
            int k;
            cin >> k;
            int max_true = 0, min_false = INT_MAX;
            for (int _ = 0; _ < k; ++_) {
                string s;
                cin >> s;
                if (min_false < 0) {
                    continue;
                }
                bool is_false = s[0] == '!';  
                if (is_false) {
                    s = s.substr(1);
                }
                if (!events.contains_str(s)) {
                    if (is_false) {
                        continue;
                    }
                    min_false = -1;
                }
                else {
                    if (is_false) {
                        min_false = min(min_false, events[s]);
                    }
                    else {
                        max_true = max(max_true, events[s]);
                    }
                    if (min_false <= max_true) {
                        min_false = -1;
                    }
                }
            }
            if (min_false < 0) {
                cout << "Plot Error\n";
            }
            else if (min_false < INT_MAX) {
                cout << cnt - min_false + 1 << " Just A Dream\n";
            }
            else {
                cout << "Yes\n";
            }
        }
    } 

    return 0;
}