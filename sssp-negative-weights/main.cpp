// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF (int)1e9

struct Edge {
    int u, v, w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};


/*
@brief The Bellman-Ford algorithm. Finds the shortest path from the given 
start node to all other nodes in the given negative-weight graph.

@param n: The number of nodes in the graph.
@param edges: The edges in the graph.
@param st: The start node.

@return A pair containing 1. a vector with the distances to each node, and 2. a vector 
with the immediate parent of each node in their shortest path. In the firstnamed vector, nodes that 
are not reachable from the start node are marked with `INF`, and nodes that can utilize a 
negative cycle in their shortest path are marked with `-INF`.

@note Time complexity: `O(n * m)`, where `n` is the number of nodes 
and `m` is the number of edges.
*/
pair<vi, vi> sssp_negative_weights(int n, vector<Edge>& edges, int st) {
    /*
    The algorithm works as follows:
    - We maintain a distance and parent vector, which respectively contain the shortest 
        distance found and the immediate parent in the corresponding path, for each node.
    - We first perform as many iterations as the number of nodes.
        - In each iteration, we:
            - Go through all edges in the graph, and if we find a new shortest path for a
                a target node, we update the designated distance and parent vectors.
    - Then, we perform the same number of iterations again, to propogate the effect of any
        potential negative cycles.
    - Once the algorithm is finished, our distance vector tells us the shortest distance to 
        each node from the start node, and the parent vector can be used to backtrack the 
        shortest path to each node.
    */

    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    for (int i = 0; i < 2 * (n - 1); ++i) {
        bool any = false;
        for (auto& e : edges) {
            if (dis[e.u] < INF && dis[e.u] + e.w < dis[e.v]) {
                dis[e.v] = (i < n - 1) ? dis[e.u] + e.w : -INF;
                par[e.v] = e.u;
                any = true;
            }
        }
        if (!any) { // stop early if no improvements are found
            break;
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
        vector<Edge> edges;
        int u, v, w;
        for (int _ = 0; _ < m; ++_) {
            cin >> u >> v >> w;
            edges.push_back(Edge(u, v, w));
        }

        pair<vi, vi> ans = sssp_negative_weights(n, edges, s);
        vi dis = ans.first;

        for (int _ = 0; _ < q; ++_) {
            int end;
            cin >> end;
            int min_dist = dis[end];

            if (min_dist == INF) {
                cout << "Impossible";
            }
            else if (min_dist == -INF) {
                cout << "-Infinity";
            }
            else {
                cout << min_dist; 
            }
            cout << '\n';
        }
    }  

    return 0;
}
