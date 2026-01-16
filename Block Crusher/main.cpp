#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF 1e9

struct Graph {
    vector<vector<pii>> adj;

    Graph(int n) : adj(n) {}

    void add_edge(int u, int v, int w=1) {
        adj[u].push_back({v, w});
    }
};

pair<vi, vi> sssp_non_negative_weights(Graph& G, int st) { 
    int n = G.adj.size();

    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    set<pii> q;
    q.insert({0, st});
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : G.adj[u]) {
            int v = edge.first, w = edge.second;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
                q.insert({dis[v], v});
            }
        }
    }
    return {dis, par};
}

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

    int h, w;
    while (cin >> h >> w && h || w) {
        vector<vector<int>> grid(h, vector<int>(w));
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                char ch; cin >> ch;
                grid[r][c] = ch - '0';
            }
        }

        vector<vector<int>> ids(h, vector<int>(w));
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                ids[r][c] = r * w + c;
            }
        }

        Graph G(h * w);
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) 
                            continue;

                        int nr = r + dr, nc = c + dc;
                        if (nr < 0 || nr >= h || nc < 0 || nc >= w)
                            continue;
                        
                        G.add_edge(ids[r][c], ids[nr][nc], grid[nr][nc]);
                    }
                }
            }
        }

        int min_dis = 2e9;
        vector<int> min_path;
        for (int c = 0; c < w; ++c) {
            int st = ids.front()[c];
            auto [dis, par] = sssp_non_negative_weights(G, st);

            for (int c2 = 0; c2 < w; ++c2) {
                int end = ids.back()[c2];
                if (dis[end] + grid.front()[c] < min_dis) {
                    min_dis = dis[end] + grid.front()[c];
                    min_path = reconstruct_shortest_path(par, st, end);
                }
            }
        }

        unordered_set<int> in_path(min_path.begin(), min_path.end());
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (in_path.find(ids[r][c]) != in_path.end())
                    cout << " ";
                else
                    cout << grid[r][c];
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
