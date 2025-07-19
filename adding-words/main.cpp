#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    map<string, int> defs;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "def") {
            string name;
            int val;
            cin >> name >> val;
            if (defs.find(name) != defs.end()) defs[name] = val;
            else defs.insert({name, val});
        } 
        else if (cmd == "calc") {
            string s;
            bool unknown = false;
            int ans = 0;
            string op = "+";
            while (true) {
                cin >> s;
                cout << s << " ";
                if (s == "=") break;
                if (s != "+" && s != "-") {
                    int val = 0;
                    if (defs.find(s) != defs.end()) {
                        val = defs[s];
                    }    
                    else {
                        unknown = true;
                    }
                    if (op == "+") ans += val;
                    else ans -= val;
                }
                else {
                    op = s;
                }
            }
            string ans_name = "";
            for (auto& kvp : defs) {
                if (kvp.second == ans) ans_name = kvp.first;
            }
            if (ans_name == "") unknown = true;
            cout << ((!unknown) ? ans_name : "unknown") << '\n';
        } 
        else if (cmd == "clear") {
            defs.clear();
        }
    }

    return 0;
}