import sys
from collections import deque


def main():
    lines = sys.stdin.read().splitlines()
    h = int(lines[0].split()[0])
    grid = []
    for i, l in enumerate(lines[1:]):
        row = [ch for ch in l]
        if i % 2 == 0:
            row.append(' ')
        grid.append(row)
    n, m = len(grid), len(grid[0])
    assert all(len(r) == m for r in grid)

    dirs = [(0, -2), (0, 2), (-1, -1), (-1, 1), (1, -1), (1, 1)]
    region_cnts = []
    for sr in range(n):
        for sc in range(m):
            if grid[sr][sc] != '.':
                continue
            q = deque([(sr, sc)])
            grid[sr][sc] = 'X'
            cnt = 1
            while q:
                r, c = q.popleft()
                for rr, cc in dirs:
                    nr, nc = r + rr, c + cc
                    if nr < 0 or nr >= n or nc < 0 or nc >= m:
                        continue
                    if grid[nr][nc] == '.':
                        q.append((nr, nc))
                        grid[nr][nc] = 'X'
                        cnt += 1
            region_cnts.append(cnt)

    region_cnts.sort(reverse=True)
    ans = 0
    for cnt in region_cnts:
        if h <= 0:
            break
        h -= cnt
        ans += 1
    print(ans)


if __name__ == "__main__":
    main()

