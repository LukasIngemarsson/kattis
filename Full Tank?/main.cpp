#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF 1e9
#define MAX_CAP 100

struct Graph {
    vector<vector<pii>> adj; // adjacency list

    Graph(int n) : adj(n) {}

    void add_edge(int u, int v, int w=1) {
        adj[u].push_back({v, w});
    }
};

int get_id(int ni, int fl) {
    return ni * (MAX_CAP + 1) + fl;
}

int get_fl(int id) {
    return id % (MAX_CAP + 1);
}

pair<vi, vi> dijkstra_with_cap(Graph& G, int st, int cap) { 
    int n = G.adj.size();

    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, st});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();

        if (d > dis[u])
            continue;

        for (auto [v, w] : G.adj[u]) {
            if (get_fl(v) > cap)
                continue;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
                q.push({dis[v], v});
            }
        }
    }
    return {dis, par};
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m; 
    cin >> n >> m;
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    vector<vector<pair<int, int>>> adj_roads(n);
    for (int i = 0; i < m; ++i) {
        int u, v, d; 
        cin >> u >> v >> d;
        adj_roads[u].push_back({v, d});
        adj_roads[v].push_back({u, d});
    }

    Graph G(n * (MAX_CAP + 1));
    for (int ni = 0; ni < n; ++ni) {
        for (int fl = 0; fl <= MAX_CAP; ++fl) {
            int u = get_id(ni, fl);
            
            if (fl < MAX_CAP) 
                G.add_edge(u, get_id(ni, fl + 1), prices[ni]);

            for (const auto& [v, d] : adj_roads[ni]) {
                if (fl >= d) 
                    G.add_edge(u, get_id(v, fl - d), 0);
            }
        }
    }

    int q; 
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int c, s, e; 
        cin >> c >> s >> e;

        auto [dis, _] = dijkstra_with_cap(G, get_id(s, 0), c);
        int ans = dis[get_id(e, 0)];
        if (ans < INF) {
            cout << ans << '\n';
        }
        else {
            cout << "impossible\n";
        }
    }

    return 0;
}
