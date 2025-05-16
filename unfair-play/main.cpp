#include <bits/stdc++.h>
using namespace std;

#define INF (int)1e9 

struct Edge {
    int u, v;
    int cap, flow = 0;
    Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
};

/*
@brief Dinic's algorithm. 
Initialize with the number of nodes `n`, the source node `s`, and the sink node `t`.
Populate the graph using `add_edge()`.
*/
struct Dinic {
    int n, s, t;
    vector<Edge> edges;
    vector<vector<int>> adj; // stores ID's of edges from each node
    vector<int> level; // stores the level of each node in the level graph
    vector<int> ptr; // used to keep track of progress (already traversed edges) between DFS runs
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t), adj(n), level(n), ptr(n) {}

    void add_edge(int u, int v, int cap) {
        // the two edges are assigned ID's edges.size() and edges.size() + 1, respectively,
        // which corresponds to their indices in `edges`
        adj[u].push_back(edges.size());
        adj[v].push_back(edges.size() + 1);
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
    }

    bool bfs() {
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : adj[u]) {
                // skip the edge if it has consumed its full capacity,
                // or if the reachable node has already been marked in the level graph
                if (edges[id].cap == edges[id].flow || level[edges[id].v] != -1) {
                    continue;
                }
                level[edges[id].v] = level[u] + 1;
                q.push(edges[id].v);
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int pushed) {
        if (pushed == 0) { // dead end, cannot push flow further
            return 0;
        }
        if (u == t) { // sink reached
            return pushed;
        }
        // we use a reference of the ptr for the node `u`, so that the 
        // we pick up where we left off in subsequent DFS runs
        for (int& cur_idx = ptr[u]; cur_idx < adj[u].size(); ++cur_idx) {
            int id = adj[u][cur_idx];
            int v = edges[id].v;
            // only take steps that lead to the next level
            if (level[u] + 1 != level[v]) {
                continue;
            }
            // push as much flow as possible to next node `v`
            int flow = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
            if (flow == 0) { // dead end, cannot push flow further
                continue;
            }
            edges[id].flow += flow;
            edges[id ^ 1].flow -= flow; // id ^ 1 XOR gives opposite edge of regular/reverse
            return flow;
        }
        return 0;
    }

    /*
    @brief Finds the maximum flow from the source node to the sink node using Dinic's algorithm.

    @return The maximum flow.

    @note Time complexity: `O(n ^ 2 * m)`, where `n` is the number of nodes and `m`
    is the number of edges. For unit networks, this algorithm works in `O(sqrt(n) * m)`.
    */
    int max_flow() {
        int tot_flow = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);

            // stop if the sink cannot be reached in the level graph
            if (!bfs()) {
                break;
            }

            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, INF)) {
                tot_flow += pushed;
            }
        }
        return tot_flow;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N, M;
    while (cin >> N >> M && N != -1) {
        vector<int> pts(N);
        for (int i = 0; i < N; ++i) 
            cin >> pts[i];

        vector<pair<int, int>> matches(M);
        unordered_set<int> disc;
        vector<int> ans(M);
        for (int i = 0; i < M; ++i) {
            int t1, t2; 
            cin >> t1 >> t2;
            --t1, --t2;
            if (t1 == N - 1) {
                ans[i] = 0;
                pts[t1] += 2;
                disc.insert(i);
            }
            else if (t2 == N - 1) {
                ans[i] = 2;
                pts[t2] += 2;
                disc.insert(i);
            }
            matches[i] = {t1, t2};
        }

        // matches = 0 to M - 1, teams = M to M + N - 1
        const int n_nodes = 2 + N + M;
        const int src = n_nodes - 1, sink = n_nodes - 2;
        Dinic dinic(n_nodes, src, sink);

        for (int i = 0; i < M; ++i) {
            if (disc.count(i)) 
                continue;
            dinic.add_edge(src, i, 2);
            dinic.add_edge(i, M + matches[i].first, 2);
            dinic.add_edge(i, M + matches[i].second, 2);
        }

        bool valid = true;
        for (int i = 0; i < N - 1; ++i) {
            if (pts[N-1] <= pts[i]) {
                valid = false;
                break;
            }
            dinic.add_edge(M + i, sink, pts[N-1] - pts[i] - 1);
        }
        if (!valid) {
            cout << "NO\n";
            continue;
        }

        int f = dinic.max_flow();
        if (f < 2 * (M - disc.size())) { // not all match pts are consumed
            cout << "NO\n";
            continue;
        }

        for (int i = 0; i < M; ++i) {
            if (disc.count(i)) 
                continue;

            auto& e = dinic.edges[dinic.adj[i].back()]; // m -> t2
            if (e.flow == 1) {
                ans[i] = 1;
            }
            else if (e.flow == 0) {
                ans[i] = 0;
            }
            else {
                ans[i] = 2;
            }
        }

        for (int i = 0; i < M; ++i) {
            if (i > 0)
                cout << " ";
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
