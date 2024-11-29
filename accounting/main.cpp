#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cin.tie(0)->sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    int def_val = 0;
    map<int, int> spec_vals;
    for (int i = 0; i < Q; ++i) {
        string event;
        int v;
        cin >> event >> v;
        if (event == "PRINT") {
            cout << ((spec_vals.find(v) != spec_vals.end()) ? spec_vals[v] : def_val) << '\n';
        }
        else if (event == "SET") {
            int num;
            cin >> num;
            spec_vals[v] = num;
        }
        else {
            spec_vals.clear();
            def_val = v;
        }
    }

    return 0;
}