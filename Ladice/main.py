import sys


sys.setrecursionlimit(300000)


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

        self.drawer_cnts = [1] * n
        self.item_cnts = [0] * n

    def find(self, a):
        if self.parent[a] != a:
            self.parent[a] = self.find(self.parent[a])
        return self.parent[a]

    def union(self, a, b):
        a_root = self.find(a)
        b_root = self.find(b)
        if a_root == b_root:
            return
        if self.rank[a_root] <= self.rank[b_root]:
            if self.rank[a_root] == self.rank[b_root]:
                self.rank[b_root] += 1
            self.parent[a_root] = b_root

            self.drawer_cnts[b_root] += self.drawer_cnts[a_root]
            self.item_cnts[b_root] += self.item_cnts[a_root]
        else:
            self.parent[b_root] = a_root 

            self.drawer_cnts[a_root] += self.drawer_cnts[b_root]
            self.item_cnts[a_root] += self.item_cnts[b_root]

def main():
    lines = iter(sys.stdin.read().splitlines())

    N, L = map(int, next(lines).split())
    uf = UnionFind(L + 1)
    print_buffer = []
    for _ in range(N):
        A_i, B_i = map(int, next(lines).split())
        uf.union(A_i, B_i)
        root = uf.find(A_i)
        if uf.item_cnts[root] < uf.drawer_cnts[root]:
            uf.item_cnts[root] += 1
            print_buffer.append("LADICA")
        else:
            print_buffer.append("SMECE")
    sys.stdout.write('\n'.join(print_buffer) + '\n')


if __name__ == "__main__":
    main()

