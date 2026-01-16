import sys
from collections import deque


def main():
    PASSABLE = '.'
    START = 'J'
    FIRE = 'F'
    DIRS = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    lines = iter(sys.stdin.read().splitlines())

    R, C = map(int, next(lines).split())
    grid = [[ch for ch in next(lines)] for _ in range(R)]
    init_fires = []
    sr, sc = -1, -1
    for r in range(R):
        for c in range(C):
            if grid[r][c] == START:
                sr, sc, = r, c
            elif grid[r][c] == FIRE:
                init_fires.append((r, c, 0))
    assert sr != -1 and sc != -1
    grid[sr][sc] = PASSABLE

    q = deque(init_fires)
    fire_ts = [[float("inf")] * C for _ in range(R)]
    vis = [[False] * C for _ in range(R)]
    for r, c, _ in init_fires:
        vis[r][c] = True
    while q:
        r, c, ts = q.popleft()
        fire_ts[r][c] = ts
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if nr < 0 or nr >= R or nc < 0 or nc >= C:
                continue
            if not vis[nr][nc] and grid[nr][nc] == PASSABLE:
                q.append((nr, nc, ts + 1))
                vis[nr][nc] = True

    q = deque([(sr, sc, 0)])
    vis = [[False] * C for _ in range(R)]
    vis[sr][sc] = True
    ans = -1
    while q:
        r, c, ts = q.popleft()
        if r == 0 or r == R - 1 or c == 0 or c == C - 1:
            ans = ts + 1
            break

        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if not vis[nr][nc] and fire_ts[nr][nc] > ts + 1 and grid[nr][nc] == PASSABLE:
                vis[nr][nc] = True
                q.append((nr, nc, ts + 1))
    print(ans if ans != -1 else "IMPOSSIBLE")


if __name__ == "__main__":
    main()

