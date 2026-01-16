#include <bits/stdc++.h>
using namespace std;

#define MAX_CLS 10

vector<string> split(string s, char delim) {
    vector<string> v;  
    int start = 0, end;
    while ((end = s.find(delim, start)) != string::npos) {
        v.push_back(s.substr(start, end - start));
        start = end + 1;
    }
    v.push_back(s.substr(start, s.size()));
    return v;
}

bool custom_comp(pair<vector<int>, string> a, pair<vector<int>, string> b) {
    if (a.first != b.first) {
        return a.first > b.first;
    }
    return a.second < b.second;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int T;
    cin >> T;
    for (int _ = 0; _ < T; ++_) {
        int n;
        cin >> n;
        
        vector<pair<vector<int>, string>> classes(n, {vector<int>(MAX_CLS, 1), ""});
        for (int i = 0; i < n; ++i) {
            string name, s, _;
            cin >> name >> s >> _;
            auto* person = &classes[i];
            person->second = name.substr(0, name.size() - 1);

            vector<string> cls = split(s, '-');
            int num_cls = cls.size();
            for (int j = 0; j < num_cls; ++j) {
                if (cls[j] == "upper") {
                    person->first[num_cls-1-j] = 2;
                }
                else if (cls[j] == "lower") {
                    person->first[num_cls-1-j] = 0;
                }
            }
        }
        sort(classes.begin(), classes.end(), custom_comp);
        for (auto& p : classes) {
            cout << p.second << '\n';
        }
        cout << string(30, '=') << '\n';
    }

    return 0;
}