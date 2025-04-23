#include <bits/stdc++.h>
using namespace std;

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
    int u, v;
    double w;

    Edge(int u, int v, double w) : u(u), v(v), w(w) {}

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

/*
@brief Finds the Minimum Spanning Tree (MST) for a given set of edges.

@param n: The number of nodes.
@param edges: A vector containing the edges.

@return A pair containing 1. the cost of the MST, and 2. the edges in the MST, if a valid solution exists.
Otherwise, 1. the cost as -1, and 2. an empty vector.

@note Time complexity: `O(|edges| * log(n))`, where `|edges|` is the number of edges 
and `n` is the number of nodes.
*/
pair<double, vector<Edge>> mst(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    double cost = 0;
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

int main() {
    cin.tie(0)->sync_with_stdio(false);

    auto l2_dist = [] (pair<double, double>& a, pair<double, double>& b) -> double {
        return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    };

    int n; cin >> n;
    while (n--) {
        int m; cin >> m;
        vector<pair<double, double>> islands(m);
        for (int i = 0; i < m; ++i) {
            cin >> islands[i].first >> islands[i].second;
        }
        vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                double dist = l2_dist(islands[i], islands[j]);
                edges.push_back(Edge(i, j, dist));
                edges.push_back(Edge(j, i, dist));
            }
        }
        auto ans = mst(m, edges);
        cout << ans.first << '\n';
    }

    return 0;
}
