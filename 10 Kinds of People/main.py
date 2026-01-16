import sys
from collections import deque


def main():
    lines = iter(sys.stdin.read().splitlines())
    R, C = map(int, next(lines).split())
    grid = [next(lines) for _ in range(R)]
    group = [[-1] * C for _ in range(R)]

    group_cnt = 0
    dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    def bfs(sr, sc):
        q = deque([(sr, sc)])
        group[sr][sc] = group_cnt
        while q:
            r, c = q.popleft()
            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                if nr < 0 or nr >= R or nc < 0 or nc >= C:
                    continue
                if group[nr][nc] == -1 and grid[r][c] == grid[nr][nc]:
                    q.append((nr, nc))
                    group[nr][nc] = group_cnt
    for r in range(R):
        for c in range(C):
            if group[r][c] != -1:
                continue
            bfs(r, c)
            group_cnt += 1

    N = int(next(lines))
    for _ in range(N):
        r1, c1, r2, c2 = map(lambda s: int(s) - 1, next(lines).split())
        if group[r1][c1] == group[r2][c2]:
            print("binary" if grid[r1][c1] == '0' else "decimal")
        else:
            print("neither")


if __name__ == "__main__":
    main()

