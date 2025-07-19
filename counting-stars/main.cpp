#include <bits/stdc++.h>
using namespace std;

int m, n;
pair<int, int> dirs[4] = {{1,0},{-1,0},{0,1},{0,-1}};

void dfs(vector<vector<char>>& grid, int r, int c) {    
    grid[r][c] = '#';
    for (auto& dir_ : dirs) {
        int newr = r + dir_.first, newc = c + dir_.second;
        if (newr < 0 || newr >= m || newc < 0 || newc >= n) continue;
        if (grid[newr][newc] == '-') {
            dfs(grid, newr, newc);
        }
    }    
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int t = 1;
    while (cin >> m >> n) {
        vector<vector<char>> grid(m, vector<char>(n, '#'));
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                cin >> grid[r][c];
            }
        }          
        int stars = 0;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == '#') continue;
                dfs(grid, r, c);
                ++stars;
            }
        }    
        cout << "Case " << t++ << ": " << stars << '\n';
    } 
    return 0;
}