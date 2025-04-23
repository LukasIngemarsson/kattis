#include <bits/stdc++.h>
using namespace std;

void dfs(int st, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& output) {
    visited[st] = true;
    for (auto u : adj[st]) {
        if (!visited[u]) {
            dfs(u, adj, visited, output);
        }
    }
    output.push_back(st);
}

/*
@brief Identifies the Strongly Connected Components (SCCs) in the graph, and creates the corresponding condensation graph.

A subset of nodes `C` is called an SCC if 
    1. for all `u`, `v` in `C` (`u` != `v`) there exists a path from `u` to `v` and from `v` to `u`, and
    2. `C` is maximal, i.e., no node can be added without violating the above condition.

@return A pair containing 1. the SCCs, and 2. the adjacency list of the condensation graph.

@note Time complexity: `O(n + m)`, where `n` is the number of nodes and `m` is the number of edges.
*/
pair<vector<vector<int>>, vector<vector<int>>> scc(vector<vector<int>>& adj) {
    int n = adj.size();

    vector<int> order; 
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, order);
        }
    }

    // create the graph's transposed adjacency list
    vector<vector<int>> rev_adj(n);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            rev_adj[v].push_back(u);
        }
    }

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    vector<vector<int>> components;
    vector<int> roots(n, 0); // stores the root node of a node's SCC
    for (auto u : order) {
        if (!visited[u]) {
            vector<int> comp;
            dfs(u, rev_adj, visited, comp);
            components.push_back(comp);
            int root = *min_element(comp.begin(), comp.end());
            for (auto v : comp) {
                roots[v] = root;
            }
        }
    }

    // create condensation adjacency list
    vector<vector<int>> cond_adj(n);
    for (int u = 0; u < n; ++u) {
        for (auto v : adj[u]) {
            if (roots[u] != roots[v]) {
                cond_adj[roots[u]].push_back(roots[v]);
            }
        }
    }

    return {components, cond_adj};
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; ++i) {
            int s1, s2;
            cin >> s1 >> s2;
            adj[s1 - 1].push_back(s2 - 1);
        }

        auto ans = scc(adj);

        auto components = ans.first;
        auto cond_adj = ans.second;

        int num_comps = components.size();
        if (num_comps == 1) {
            cout << 0 << '\n';
            continue;
        }

        unordered_set<int> not_root;
        int num_leaves = 0;
        for (auto& comp : components) {
            int root = *min_element(comp.begin(), comp.end());
            auto& neighbors = cond_adj[root];
            if (neighbors.empty()) {
                ++num_leaves;
            }
            else {
                for (auto u : neighbors) {
                    not_root.insert(u);
                }
            }
        }
        int num_roots = num_comps - not_root.size();
        cout << max(num_roots, num_leaves) << '\n';
    }

    return 0;
}
