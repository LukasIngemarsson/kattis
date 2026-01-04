import sys
from collections import deque


sys.setrecursionlimit(10**6)


def find_bridges(st, adj):
    N = len(adj)
    bridges = set()
    vis = [False] * N
    tin = [-1] * N
    low = [-1] * N
    timer = 1
    def dfs(v, p=-1):
        nonlocal timer
        vis[v] = True
        timer += 1
        tin[v] = low[v] = timer
        parent_skipped = False
        for to in adj[v]:
            if to == p and not parent_skipped:
                parent_skipped = True
                continue
            if vis[to]:
                low[v] = min(low[v], tin[to])
            else:
                dfs(to, v)
                low[v] = min(low[v], low[to])
                if low[to] > tin[v]:
                    bridges.add(tuple(sorted((v, to))))
    dfs(st)
    return bridges


def main():
    lines = iter(sys.stdin.read().splitlines())
    N, M = map(int, next(lines).split()) 
    adj = [[] for _ in range(N)]
    for _ in range(M):
        u, v = map(int, next(lines).split()) 
        adj[u].append(v)
        adj[v].append(u)

    bridges = find_bridges(0, adj)
    q = deque([0]) 
    seen = {0}
    while q:
        cur = q.popleft()
        for nbr in adj[cur]:
            if nbr in seen or tuple(sorted((cur, nbr))) in bridges:
                continue
            q.append(nbr)
            seen.add(nbr)
    ans = len(seen)
    print(ans)


if __name__ == "__main__":
    main()

