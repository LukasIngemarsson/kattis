#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N;
    cin >> N;
    map<string, int> cnts;
    for (int _ = 0; _ < N; ++_) {
        string w, temp = "";
        cin >> w;
        for (int i = 0; i < w.size(); ++i) {
            temp.push_back(w[i]);
            ++cnts[temp];
        }
        cout << cnts[w] - 1 << '\n';
    } 

    return 0;
}