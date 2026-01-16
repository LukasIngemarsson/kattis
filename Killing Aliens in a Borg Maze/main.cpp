#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
@brief Given an initial number of elements, each belonging to a distinct set, 
Union Find provides efficient union and find operations.

@note Memory complexity: `O(n)`, where `n` is the number of elements.
*/
struct UnionFind {
    // parent: create a tree structure for each set, where an element points to a parent
    // rank: stores the rank of a tree at the root index
    vector<int> parent, rank;
    
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    } 

    /*
    @brief Finds the root parent for a given element. This indicates which set the element belongs to.

    @param a: The element whose set we want to identify.

    @return The root element representing the set.

    @note Time complexity: `Oam(a(n))` ~= `Oam(1)`, where `a` is the inverse ackermann function,
    and `n` is the number of elements.
    */
    int find(int a) {
        if (parent[a] != a) {
            // update parent to root for each element that we find while climbing the tree (path compression)
            parent[a] = find(parent[a]);
        }
        return parent[a];
    }

    /*
    @brief Merges the two sets containing the two given elements. 

    @param a: The first element.
    @param b: The second element.

    @note Time complexity: `Oam(a(n))` ~= `Oam(1)`, where `a` is the inverse ackermann function,
    and `n` is the number of elements.
    */
    void union_(int a, int b) {
        int a_root = find(a), b_root = find(b);
        if (a_root == b_root) {
            return;
        }
        // decide which tree attaches to the other based on their rank
        if (rank[a_root] < rank[b_root]) {
            parent[a_root] = parent[b_root];
        }
        else if (rank[a_root] > rank[b_root]) {
            parent[b_root] = parent[a_root];
        }
        else {
            parent[a_root] = parent[b_root];
            ++rank[b_root];
        }
    }

    /*
    @brief Checks if the two given elements belong to the same set.

    @param a: The first element.
    @param b: The second element.

    @return A boolean value representing if the elements share the same set.

    @note Time complexity: `Oam(a(n))` ~= `Oam(1)`, where `a` is the inverse ackermann function,
    and `n` is the number of elements.
    */
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

struct Edge {
    int u, v, w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

/*
@brief Finds the Minimum Spanning Tree (MST) for a given set of edges, using Kruskal's algorithm.

@param n: The number of nodes.
@param edges: A vector containing the edges.

@return A pair containing 1. the cost of the MST, and 2. the edges in the MST, if a valid solution exists.
Otherwise, 1. the cost as -1, and 2. an empty vector.

@note Time complexity: `O(m * log(n))`, where `m` is the number of edges 
and `n` is the number of nodes.
*/
pair<ll, vector<Edge>> mst(int n, vector<Edge> edges) {
    /*
    The algorithm works as follows:
    - First, we sort the given vector of edges based on their weights.
    - We initialize a UnionFind struct, which we use to efficiently keep track 
        of which nodes belong to the same set, as well as to merge these sets.
    - We also initialize a variable to store the total cost of the MST,
        as well as a vector to store the edges present in the MST.
    - Then, for each edge in the sorted edges, we:
        - Check if the nodes share the same set, and if they do not, we:
            - Merge / take the union of the sets that the respective nodes
                belong to.
            - Check if the size of the MST vector is equal to the number of
                nodes minus 1, and if it is, we interrupt the loop.
    - If the size of the MST vector is less than the number of nodes minus 1
        after we finish the loop, then we can determine that no solution exists
        for the given set of edges.
    - Otherwise, we have our solution.
    */

    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    ll cost = 0;
    vector<Edge> res;
    for (Edge& e : edges) {
        if (!uf.same(e.u, e.v)) {
            cost += e.w;
            res.push_back(e);
            uf.union_(e.u, e.v);

            if (res.size() == n - 1)
                break;
        }
    } 
    if (res.size() < n - 1) { // no valid MST
        return {-1, vector<Edge>()};
    }
    return {cost, res};
}

struct Tr {
    int r, c, d;
    Tr (int r, int c, int d) : r(r), c(c), d(d) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    pair<int, int> dirs[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int N;
    cin >> N;
    while (N--) {
        int x, y;
        cin >> x >> y; cin.ignore();

        vector<string> grid(y);
        map<pair<int, int>, int> nodes;
        for (int i = 0; i < y; ++i) {
            getline(cin, grid[i]);
            for (int j = 0; j < x; ++j) {
                if (grid[i][j] == 'S' || grid[i][j] == 'A')
                    nodes[{i, j}] = nodes.size();
            }
        }

        int n = nodes.size();
        vector<Edge> edges;
        for (const auto& [p, id] : nodes) {
            vector<vector<bool>> vis(y, vector<bool>(x));
            queue<Tr> q;
            q.emplace(p.first, p.second, 0);

            while (!q.empty()) {
                auto [r, c, d] = q.front(); q.pop();

                if (vis[r][c])
                    continue;

                vis[r][c] = true;

                if (nodes.find({r, c}) != nodes.end()) 
                    edges.emplace_back(id, nodes[{r, c}], d);

                for (const auto& [dr, dc] : dirs) {
                    if (grid[r+dr][c+dc] != '#')
                        q.emplace(r + dr, c + dc, d + 1);
                }
            }
        }

        cout << mst(n, edges).first << '\n';
    }

    return 0;
}
