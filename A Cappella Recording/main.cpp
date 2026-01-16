#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, d;
    cin >> n >> d;
    vector<int> notes(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> notes[i];
    }    
    sort(notes.begin(), notes.end());

    int ans = 1, diff = 0, prev = notes[0];
    for (int i = 0; i < n; ++i) {
       int pitch = notes[i];
       diff += (pitch - prev);
       if (diff > d) {
            diff = 0;
            ++ans;
       }
       prev = pitch;
    }
    cout << ans;

    return 0;
}