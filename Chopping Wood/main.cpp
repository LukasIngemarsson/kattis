#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> v(n), last_app(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        last_app[--v[i]] = i;
    }

    set<int> leaves; 
    for (int i = 0; i <= n; ++i) {
        if (last_app[i] == -1) {
            leaves.insert(i);
        }
    }

    vector<int> u(n);
    bool valid = true;
    if (v.back() != n) {
        valid = false;
    }
    else {
        for (int i = 0; i < n; ++i) {
            if (leaves.size() == 0) {
                valid = false;
                break;
            }
            u[i] = *leaves.begin() + 1;
            leaves.erase(leaves.begin());
            if (last_app[v[i]] == i) {
                leaves.insert(v[i]);
            }
        }
    }

    if (valid) {
        for (int i = 0; i < n; ++i) {
            cout << u[i] << '\n';
        }
    }
    else {
        cout << "Error\n";
    }

    return 0;
}