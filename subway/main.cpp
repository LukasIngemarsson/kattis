// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF 1e9

struct Graph {
    vector<vector<pair<int, double>>> adj; // adjacency list

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
pair<vector<double>, vector<int>> sssp_non_negative_weights(Graph& G, int st) { 
    int n = G.adj.size();

    // dis: stores shorest distance from st to all nodes
    // par: stores the parent node that is used to reach each node in its shortest path 
    vector<double> dis(n, INF);
    vector<int> par(n, -1);
    dis[st] = 0;
    set<pair<double, int>> q; // queue of {dist, node} pairs
    q.insert({0, st});
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : G.adj[u]) {
            int v = edge.first;
            double w = edge.second;
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

    const double WALK_SPEED = 10 / 3.6;
    const double SUB_SPEED = 40 / 3.6;
    const int MAX_NODES = 200 + 2;

    auto l2_dist = [] (int x1, int y1, int x2, int y2) {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    };

    vector<pair<double, double>> coords(MAX_NODES);

    // 0 is start and 1 is end
    cin >> coords[0].first >> coords[0].second;
    cin >> coords[1].first >> coords[1].second;
    Graph G(MAX_NODES);

    int node_cnt = 2; 

    double x1, y1;
    while (cin >> x1 >> y1) {
        double x2, y2;
        while (true) {
            coords[node_cnt] = {x1, y1};
            cin >> x2 >> y2;

            if (x2 == -1 && y2 == -1) {
                ++node_cnt;
                break;
            }

            G.add_edge(node_cnt, node_cnt + 1, l2_dist(x1, y1, x2, y2) / SUB_SPEED);
            ++node_cnt;
            x1 = x2, y1 = y2;
        }
    }

    for (int i = 0; i < node_cnt; ++i) {
        for (int j = i + 1; j < node_cnt; ++j) {
            double x1 = coords[i].first, y1 = coords[i].second;
            double x2 = coords[j].first, y2 = coords[j].second;
            G.add_edge(i, j, l2_dist(x1, y1, x2, y2) / WALK_SPEED);
        }
    }

    cout << round(sssp_non_negative_weights(G, 0).first[1] / 60.0) << '\n';

    return 0;
}