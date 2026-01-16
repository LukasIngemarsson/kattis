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
    vector<Edge> edges;
    vector<vector<int>> adj; // each entry in each list is an ID of the corresponding edge
    int n, s, t;
    vector<int> level, ptr; // ptr is used in DFS to avoid revisiting dead ends
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t), adj(n), level(n), ptr(n) {}

    void add_edge(int u, int v, int cap) {
        adj[u].push_back(edges.size());
        adj[v].push_back(edges.size() + 1);
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
    }

    bool bfs() {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
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
        if (u == t) {
            return pushed;
        }
        for (int& cid = ptr[u]; cid < adj[u].size(); ++cid) {
            int id = adj[u][cid];
            int v = edges[id].v;
            if (level[u] + 1 != level[v]) {
                continue;
            }
            int flow = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
            if (flow == 0) {
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

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int node_cnt = 0;
        unordered_map<string, int> res_to_id, party_to_id, club_to_id;
        vector<string> id_to_str;
        unordered_map<string, int> dupe_cnt;

        map<int, vector<int>> party_to_mems, mem_to_clubs;
        unordered_set<int> clubs;
        string delim = "_";
        
        auto which_map = [&] (int which) -> unordered_map<string, int>& {
            if (which == 0) { // resident
                return res_to_id;
            }
            if (which == 1) { // party 
                return party_to_id;
            }
            else { // club
                return club_to_id;
            }
        };

        auto assign_id = [&] (string s, int which) -> int {
            auto& m = which_map(which);
            if (m.find(s) == m.end()) {
                m[s] = node_cnt++;
                id_to_str.push_back(s);
                if (which == 0) dupe_cnt[s] = 0;
            }
            else if (which == 0) { // handle residents with the same name
                s += delim + to_string(dupe_cnt[s]++);
                m[s] = node_cnt++;
                id_to_str.push_back(s);
            }
            return m[s];
        };

        string res, party;
        for (int i = 0; i < n; ++i) {
            cin >> res >> party;
            int rid = assign_id(res, 0), pid = assign_id(party, 1);
            party_to_mems[pid].push_back(rid);

            int C; cin >> C;
            string club;
            for (int j = 0; j < C; ++j) {
                cin >> club;
                int cid = assign_id(club, 2);
                clubs.insert(cid);
                mem_to_clubs[rid].push_back(cid);
            }
        }
        int src = node_cnt++;
        int sink = node_cnt++;
        Dinic dinic(node_cnt, src, sink);

        int below_half = (clubs.size() - 1) / 2;
        for (auto& kvp: party_to_mems) {
            int pid = kvp.first;
            auto mems = kvp.second;
            dinic.add_edge(src, pid, below_half);

            for (auto mid : mems) {
                dinic.add_edge(pid, mid, 1);
            }
        }

        for (auto& kvp : mem_to_clubs) {
            int mid = kvp.first;
            auto clubs = kvp.second;

            for (auto c : clubs) {
                dinic.add_edge(mid, c, 1);
            }
        }
        for (auto& cid : clubs) {
            dinic.add_edge(cid, sink, 1);
        }

        if (dinic.max_flow() < clubs.size()) {
            cout << "Impossible.\n";
        }
        else {
            string a, b;
            for (auto& e : dinic.edges) {
                if (e.flow > 0 && mem_to_clubs.find(e.u) != mem_to_clubs.end() &&
                    clubs.find(e.v) != clubs.end()) {
                    cout << id_to_str[e.u] << " " << id_to_str[e.v] << '\n';
                }
            }
        }
        if (T > 0) cout << '\n';
    }

    return 0;
}
