import sys
from queue import PriorityQueue


def main():
    lines = sys.stdin.read().splitlines()
    R, C = map(int, lines[0].split())
    grid = [list(map(int, l.split())) for l in lines[1:]]

    MAX_DEPTH = 10**7
    dp = [[MAX_DEPTH + 1] * C for _ in range(R)]
    dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    q = PriorityQueue()
    for r in range(R):
        q.put((0, r, 0))
    while not q.empty():
        max_depth, r, c = q.get()
        if dp[r][c] <= max_depth:
            continue
        dp[r][c] = max(max_depth, grid[r][c])
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if nr < 0 or nr >= R or nc < 0 or nc >= C:
                continue
            if dp[r][c] < dp[nr][nc]:
                q.put((dp[r][c], nr, nc))

    ans = min(dp[r][-1] for r in range(R))
    print(ans)


if __name__ == "__main__":
    main()

