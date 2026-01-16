#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N;
    set<char> vowels = {'a','e','i','o','u','y'};
    while (true) {
        cin >> N;
        if (!N) break;
        vector<string> words(N, "");
        pair<int, int> fav = {-1, -1};
        for (int i = 0; i < N; ++i) {
            cin >> words[i];
            int count = 0;
            for (int j = 0; j < words[i].size() - 1; ++j) {
                if (vowels.find(words[i][j]) != vowels.end() &&
                     words[i][j] == words[i][j+1]) {
                        ++count;
                     }
            }
            if (count > fav.first) fav = {count, i};
        }
        cout << words[fav.second] << '\n';
    }
    return 0;
}