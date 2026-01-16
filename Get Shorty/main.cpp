#include <bits/stdc++.h>
using namespace std;

typedef pair<int, double> pid;
typedef vector<int> vi;
typedef vector<double> vd;

struct Graph {
    vector<vector<pid>> adj; // adjacency list

    Graph(int n) : adj(n) {}

    void add_edge(int u, int v, double w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
};

/*
@brief Dijkstra's algorithm. Finds the shortest path from the given 
start node to all other nodes in the given non-negative-weight graph.

@param G: The graph.
@param st: The start node.

@return A pair containing 1. a vector with the distances to each node, and 2. a vector 
with the immediate parent of each node in their shortest path.

@note Time complexity: `O(m * log(n))`, where `m` is the number of edges and `n` is the number 
of nodes in the graph.
@note Good for sparse graphs.
*/
pair<vd, vi> dijkstra(Graph& G, int st) { 
    int n = G.adj.size();
    // dis: stores shorest distance from st to all nodes
    // par: stores the parent node that is used to reach each node in its shortest path 
    vd dis(n, -1);
    vi par(n, -1);
    dis[st] = 1;
    set<pid> q; // queue of {node, dist} pairs
    q.insert({st, 1});
    while (!q.empty()) {
        int u = q.begin()->first;
        q.erase(q.begin());

        for (auto edge : G.adj[u]) {
            int v = edge.first;
            double w = edge.second;
            if (dis[v] == -1 || dis[u] * w > dis[v]) {
                dis[v] = dis[u] * w;
                par[v] = u;
                q.insert({v, dis[v]});
            }
        }
    }
    return {dis, par};
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    while (cin >> n >> m && n && m) {
        Graph G(n);
        for (int i = 0; i < m; ++i) {
            int x, y;
            double f;
            cin >> x >> y >> f;
            G.add_edge(x, y, f);
        }
        cout << fixed << setprecision(4) << dijkstra(G, 0).first.back() << '\n';
    }

    return 0;
}
