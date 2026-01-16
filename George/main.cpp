#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF 1e9

struct Edge {
    int v, d, gst, gend;

    Edge(int v, int d, int gst, int gend) : v(v), d(d), gst(gst), gend(gend) {}

     // calculates the total edge weight, i.e., distance + time wait needed
    int calc_weight(int t) {
        if (t >= gst && t < gend) {
            return d + (gend - t);
        }
        return d;
    }
};

struct Graph {
    vector<vector<Edge>> adj; // adjacency list

    Graph(int n) : adj(n) {}

    void add_edge(int u, int v, int d, int gst = -1, int ge = -1) {
        adj[u].push_back(Edge(v, d, gst, ge));
        adj[v].push_back(Edge(u, d, gst, ge));
    }
};

/*
@brief Finds the shortest path from the given start node to all other nodes in the given graph.

@param G: The graph.
@param st: The start node.

@return A pair containing 1. a vector with the distances to each node, and 2. a vector 
with the parent of each node in their shortest path.

@note Time complexity: `O(m * log(n))`, where `m` is the number of edges and `n` is the number 
of nodes in the graph.
@note Good for sparse graphs.
*/
pair<vi, vi> dijkstra(Graph& G, int st) { 
    int n = G.adj.size();

    // dis: stores shorest distance from st to all nodes
    // par: stores the parent node that is used to reach each node in its shortest path 
    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    set<pii> q; // queue of {dist, node} pairs
    q.insert({0, st});
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : G.adj[u]) {
            int v = edge.v, w = edge.calc_weight(dis[u]);
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
                q.insert({dis[v], v});
            }
        }
    }
    return {dis, par};
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    int st, end, t0, g;
    cin >> st >> end >> t0 >> g;
    --st, --end;

    vector<int> g_route(g);
    for (int i = 0; i < g; ++i) {
        cin >> g_route[i];
        --g_route[i];
    }

    map<pii, int> edge_to_d;
    for (int _ = 0; _ < M; ++_) {
        int u, v, d;
        cin >> u >> v >> d;
        --u, --v;
        edge_to_d[{min(u, v), max(u, v)}] = d;
    }

    Graph G(N);
    int t = -t0;
    for (int i = 1; i < g; ++i) {
        int a = g_route[i - 1], b = g_route[i];
        pii p = {min(a, b), max(a, b)};
        int d = edge_to_d[p];
        G.add_edge(p.first, p.second, d, t, t + d);
        t += d;
        edge_to_d.erase(p);
    }
    for (auto& kvp : edge_to_d) {
        auto p = kvp.first;
        G.add_edge(p.first, p.second, kvp.second);
    }

    auto dijk = dijkstra(G, st);
    auto ans = dijk.first[end]; 
    cout << ans << '\n';

    return 0;
}
