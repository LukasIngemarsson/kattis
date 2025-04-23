// Author: Lukas Ingemarsson
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

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    UnionFind uf(N);
    for (int i = 0; i < Q; ++i) {
        char ch;
        int a, b;
        cin >> ch >> a >> b;

        if (ch == '?') {
            cout << ((uf.same(a, b)) ? "yes" : "no") << '\n';
        }
        else if (ch == '=') {
            uf.union_(a, b);
        }
    }

    return 0;
}