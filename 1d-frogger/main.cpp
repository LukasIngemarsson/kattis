#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, s, m;
    cin >> n >> s >> m;
    vector<int> squares(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> squares[i];
    }
    int pos = s - 1;
    int hops = 0;
    set<int> visited;
    while (true) {
        if (visited.find(pos) != visited.end()) {
            cout << "cycle\n";
            break;
        }
        visited.insert(pos);
        int num = squares[pos];
        if (num == m) {
            cout << "magic\n";
            break;
        }
        if (pos < 0) {
            cout << "left\n";
            break;
        }
        else if (pos >= n) {
            cout << "right\n";
            break;
        }
        if (num > 0) pos += num;
        else pos -= -num;
        ++hops;
    }
    cout << hops;
    return 0;
}