import sys


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n)) 
        self.rank = [0] * n
        self.cnt = [1] * n

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
            self.cnt[b_root] += self.cnt[a_root]
        else:
            self.parent[b_root] = a_root
            self.cnt[a_root] += self.cnt[b_root]


def main():
    input_iter = iter(sys.stdin.read().split())
    T = int(next(input_iter))
    print_buffer = []
    for _ in range(T):
        F = int(next(input_iter))
        names = set()
        friends = []
        for _ in range(F):
            a, b = next(input_iter), next(input_iter)
            friends.append((a, b))
            names.add(a)
            names.add(b)
        names = list(names)
        name_to_id = {n: i for i, n in enumerate(names)}
        uf = UnionFind(len(names)) 
        for a, b, in friends:
            a_id = name_to_id[a]
            b_id = name_to_id[b]
            uf.union(a_id, b_id)
            ans = uf.cnt[uf.find(a_id)]
            print_buffer.append(ans)
    for res in print_buffer:
        sys.stdout.write(str(res) + '\n')


if __name__ == "__main__":
    main()

