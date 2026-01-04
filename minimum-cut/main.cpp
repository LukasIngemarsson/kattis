#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
#define INF (int)1e9 

struct Edge {
    int u, v, f;

    Edge(int u, int v, int f) : u(u), v(v), f(f) {}
};

struct Graph {
    int n;
    vvi adj; 
    vvi cap; // residual capacity of each edge
    set<pii> edges; // used to prevent adding duplicates to the adjacency list

    Graph(int n) : n(n), adj(n), cap(n, vi(n)) {}

    void add_edge(int u, int v, int c) {
        // pairs of nodes with multiple edges between each other
        // are simply represented by a single edge with their joint capacity
        pii e = {min(u, v), max(u, v)};
        if (edges.find(e) == edges.end()) {
            adj[u].push_back(v);
            adj[v].push_back(u); // add reverse edge to allow flow backwards
            cap[v][u] = 0; // set reverse edge capacity to zero
            edges.insert(e);
        }
        cap[u][v] += c;
    }
};

int bfs(Graph& G, int s, int t, vi& par) {
    fill(par.begin(), par.end(), -1);

    queue<pii> q;
    q.push({s, INF});
    par[s] = -2; // source has no parent
    while(!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int nxt : G.adj[cur]) {
            if (par[nxt] == -1 && G.cap[cur][nxt]) {
                par[nxt] = cur;
                int new_flow = min(flow, G.cap[cur][nxt]);
                if (nxt == t) {
                    return new_flow;
                }
                q.push({nxt, new_flow});
            }
        }
    }
    return 0;
}

/*
@brief Finds the maximum flow from a given source to sink node in the 
provided graph, using the Edmonds-Karp algorithm. Edmonds-Karp is an implementation
of Ford-Fulkerson that uses BFS to find augmenting paths.

@param G: The graph.
@param s: The source node.
@param t: The sink node.

@return A pair containing 1. the maximum flow, and 2. the edges used in the flow graph, 
where each entry contains (from, to, flow).

@note Time complexity: `O(n * m ^ 2)`, where `n` is the number of nodes and `m`
is the number of edges.
@note The input Graph will be updated in-place, thus containing the final state of the graph
after the algorithm is complete.
*/
pair<int, vector<Edge>> max_flow(Graph& G, int s, int t) {
    int n = G.n;
    vi par(n); // parent of each node in the path
    vvi flows(n, vi(n)); // flow of each edge

    int tot_flow = 0;
    while (int new_flow = bfs(G, s, t, par)) {
        tot_flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = par[cur];
            // adjust residual capacity of edges in path
            G.cap[prev][cur] -= new_flow;
            G.cap[cur][prev] += new_flow;
            // update flow
            flows[prev][cur] += new_flow;
            flows[cur][prev] -= new_flow;
            cur = prev;
        }
    }

    vector<Edge> used_edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (flows[i][j] > 0) {
                used_edges.push_back(Edge(i, j, flows[i][j]));
            }
        }
    }

    return {tot_flow, used_edges};
}

void dfs(const Graph& G, int u, unordered_set<int>& U) {
    U.insert(u);
    for (int v : G.adj[u]) {
        if (G.cap[u][v] > 0 && U.find(v) == U.end()) {
            dfs(G, v, U);
        }
    }
}

/*
@brief Finds the minimum cut in the given graph, for the given source and sink node.
A minimal cut is a subset `U` of the nodes `V` where the sum of the capacities from U to 
the rest of the nodes `U \ V` is minimal.

@param G: The graph.
@param s: The source node.
@param t: The sink node.

@return A set containing the nodes in the minimal cut.

@note Time complexity: `O(n * m ^ 2)`, where `n` is the number of nodes and `m`
is the number of edges.
@note The input Graph will be updated in-place, thus containing the final state of the graph
after the algorithm is complete.
*/
unordered_set<int> min_cut(Graph& G, int s, int t) {
    max_flow(G, s, t);
    unordered_set<int> U;
    dfs(G, s, U);
    return U;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add_edge(u, v, w);
    }

    auto U = min_cut(G, s, t);

    cout << U.size() << '\n';
    for (int u : U) {
        cout << u << '\n';
    }

    return 0;
}
