#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF 1e9

struct Edge {
    int v, t0, P, d;

    Edge(int v, int t0, int P, int d) : v(v), t0(t0), P(P), d(d) {}

    // calculates the total edge weight, i.e., distance + time wait needed
    int calc_weight(int t) {
        if (P == 0 && t > t0) {
            return INF;
        }
        if (t <= t0) {
            return d + (t0 - t);
        }
        int cycle = (t - t0 - 1) / P;
        return d + (t0 + P * (cycle + 1) - t);
    }
};

struct Graph {
    vector<vector<Edge>> adj; // adjacency list

    Graph(int n) : adj(n) {}

    void add_edge(int u, int v, int t0, int P, int d) {
        adj[u].push_back(Edge(v, t0, P, d));
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
@note Memory complexity: `O(n)`, where `n` is the number of nodes in the graph.
@note Good for sparse graphs.
*/
pair<vi, vi> sssp_non_negative_weights(Graph& G, int st) { 
    /*
    The algorithm works as follows:
    - We maintain a priority queue, or in this case a set, containing {dist, node} pairs.
        - It is initialized to contain the pair representing the distance from the start node
            to itself.
    - We also maintain a distance and parent vector, which respectively contain the shortest 
        distance found and the immediate parent in the corresponding path, for each node.
    - Then, as long as the queue is not empty, we:
        - Take the first element in the queue, i.e., the element with the shortest distance
            from the start node.
        - Look at the edges from this node, and if we find a distance to any neighboring node
            that is shorter than any previously found path, we store the new distance and the
            parent node in the designated vectors, and enqueue the new {dist, node} pair.
    - Once the algorithm is finished, our distance vector tells us the shortest distance to 
        each node from the start node, and the parent vector can be used to backtrack the 
        shortest path to each node.
    */

    int n = G.adj.size();

    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    set<pii> q;
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

/*
@brief Reconstructs the shortest path from the given start to end node.

@param par: A vector containing the immediate parent of each node in 
their shortest path, which can be backtracked to retreive the full path.

@return A vector containing the shortest path in the order from start to end. 
This vector is empty if no shortest path exists for the start-end pair.
*/
vi reconstruct_shortest_path(vector<int>& par, int st, int end) {
    vi path;
    for (int u = end; u != st; u = par[u]) {
        if (u == -1) {
            return vi();
        }
        path.push_back(u);
    }
    path.push_back(st);

    reverse(path.begin(), path.end()); 
    return path;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m, q, s;
    while (cin >> n >> m >> q >> s && n || m || q || s) {
        Graph G(n);
        int u, v, t0, P, d;
        for (int _ = 0; _ < m; ++_) {
            cin >> u >> v >> t0 >> P >> d;
            G.add_edge(u, v, t0, P, d);
        }

        pair<vi, vi> ans = sssp_non_negative_weights(G, s);
        vi dis = ans.first, par = ans.second;

        for (int _ = 0; _ < q; ++_) {
            int end;
            cin >> end;
            int min_dist = dis[end];

            if (min_dist < INF) {
                cout << min_dist;
            }
            else {
                cout << "Impossible";
            }
            cout << '\n';
        }
    }

    return 0;
}
