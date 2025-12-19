#include <bits/stdc++.h>
using namespace std;

#define NUM_CONTENTS 5

pair<bool, double> get_cals(int i, string s) {
    int s_len = s.size();
    double val = stoi(s.substr(0, s_len - 1));
    char metric = s[s_len-1];
    switch (metric) {
        case 'g':
            if (i == 0) return {true, 9 * val};
            else if (i == NUM_CONTENTS - 1) return {true, 7 * val};
            else return {true, 4 * val};
        case 'C':
            return {true, val};
        case '%':
            return {false, val};
        default:
            return {true, -1};
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string content[NUM_CONTENTS]; // f, p, s, st, a
    bool prev_was_end = false;
    double ttotal = 0, fat_cals = 0;
    while(true) {
        double total = 0, perc = 0;
        cin >> content[0];
        if (content[0] == "-") {
            if (prev_was_end) break;
            prev_was_end = true;
            cout << static_cast<int>(round(100 * (fat_cals / ttotal))) << "%\n";
            ttotal = 0, fat_cals = 0;
            continue;
        }
        else {
            prev_was_end = false;
        }
        for (int i = 0; i < NUM_CONTENTS; ++i) {
            if (i > 0) cin >> content[i];
            pair<bool, double> p = get_cals(i, content[i]);
            if (p.first) {
                total += p.second;
            }
            else {
                perc += p.second;
            }
        }
        total /= (1 - perc / 100);
        ttotal += total;
        pair<bool, double> fp = get_cals(0, content[0]);
        fat_cals += (fp.first) ? fp.second : (fp.second / 100) * total;
    }
    return 0;
}
