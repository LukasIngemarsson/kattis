#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;

    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        cout << s.size() << '\n';
    }

    return 0;
}