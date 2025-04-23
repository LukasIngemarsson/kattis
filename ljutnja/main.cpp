#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    long long M, N;
    cin >> M >> N;
    vector<long long> wishes(N); 
    for (long long i = 0; i < N; ++i) {
        cin >> wishes[i];
    }
    sort(wishes.begin(), wishes.end(), greater<>());

    long long low = 0, high = 2e9;
    while (low < high) {
        long long max_ungranted = (low + high) / 2;
        long long cost = 0;
        for (long long i = 0; i < N && cost <= M; ++i) {
            if (wishes[i] > max_ungranted) {
                cost += (wishes[i] - max_ungranted);
            }
            else {
                break;
            }
        }
        if (cost > M) {
            low = max_ungranted + 1;
        }
        else {
            high = max_ungranted;
        }
    }
    for (long long i = 0; i < N; ++i) {
        if (wishes[i] < low) {
            break;
        }
        M -= wishes[i] - low;
        wishes[i] = low;
    }
    long long ans = 0;
    for (long long w : wishes) {
        if (M-- > 0) --w;
        ans += w * w;
    }
    cout << ans << '\n';

    return 0;
}