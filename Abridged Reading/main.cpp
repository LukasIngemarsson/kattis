#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m; 
    cin >> n >> m;
    vector<int> costs(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> costs[i];
    }
    vector<int> adj_list(n + 1);
    unordered_set<int> prereqs;
    for (int _ = 0; _ < m; ++_) {
        int from, to;
        cin >> from >> to;
        adj_list[to] = from;
        prereqs.insert(from);
    }
    vector<vector<int>> paths;
    vector<int> path;
    for (int i = 1; i <= n; ++i) {
        if (prereqs.find(i) == prereqs.end()) {
            path.push_back(i);
            while (adj_list[path.back()] != 0) {
                path.push_back(adj_list[path.back()]);
            }
            paths.push_back(path);
            path.clear();
        }
    }
    auto calc_cost = [&costs] (unordered_set<int>& nodes) -> int {
        int cost = 0;
        for (int node : nodes) {
            cost += costs[node];
        }
        return cost;
    };
    int min_cost = INT_MAX;
    unordered_set<int> nodes;
    for (int i = 0; i < paths.size(); ++i) {
        for (int j = i + 1; j < paths.size(); ++j) {
            nodes.insert(paths[i].begin(), paths[i].end());
            nodes.insert(paths[j].begin(), paths[j].end());
            min_cost = min(min_cost, calc_cost(nodes));
            nodes.clear();
        }
    }
    cout << min_cost;

    return 0;
}