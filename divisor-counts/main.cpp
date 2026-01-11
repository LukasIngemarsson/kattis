#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N;
    cin >> N;

    vector<int> divs(N + 1);
    for (int i = 1; i <= N; ++i) {
        for (int j = i; j <= N; j += i) {
            ++divs[j];
        }
        cout << divs[i] << '\n';
    }

    return 0;
}
