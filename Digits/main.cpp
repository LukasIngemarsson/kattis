#include <iostream>
#include <string>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string line;

    while (true) {
        cin >> line;

        if (line == "END") break;

        int i = 0;
        string prev, curr = line;

        while (curr != prev) {
            prev = curr;
            curr = to_string(curr.size());
            i++;
        }
        cout << i << '\n';
    }
    return 0;
}