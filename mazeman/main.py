import sys
from collections import deque


def main():
    lines = iter(sys.stdin.read().splitlines())
    N, M = map(int, next(lines).split())
    grid = [[ch for ch in next(lines)] for _ in range(N)]

    doors = set()
    for c in range(1, M - 1):
        for r in (0, N - 1):
            if 'A' <= grid[r][c] <= 'W':
                doors.add((r, c))
    for r in range(N):
        for c in (0, M - 1):
            if 'A' <= grid[r][c] <= 'W':
                doors.add((r, c))

    DIRS = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    min_doors = 0
    for sr, sc in doors:
        if grid[sr][sc] == 'X':
            continue
        q = deque([(sr, sc)]) 
        grid[sr][sc] = 'X'
        has_eaten = False
        while q:
            r, c = q.popleft()
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                both_are_doors = (r, c) in doors and (nr, nc) in doors
                oob = nr < 0 or nr >= N or nc < 0 or nc >= M
                if oob or grid[nr][nc] == 'X' or both_are_doors:
                    continue
                if grid[nr][nc] == '.':
                    has_eaten = True
                grid[nr][nc] = 'X'
                q.append((nr, nc))
        if has_eaten:
            min_doors += 1
    unreachable = 0
    for r in range(N):
        for c in range(M):
            if grid[r][c] == '.':
                unreachable += 1
    print(min_doors, unreachable)


if __name__ == "__main__":
    main()

