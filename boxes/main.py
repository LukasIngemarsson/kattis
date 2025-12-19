import sys


def main():
    lines = iter(sys.stdin.read().splitlines())
    N = int(next(lines))
    tree = [[] for _ in range(N)]  
    containers = list(map(int, next(lines).split()))
    for i, c in enumerate(containers):
        if c != 0:
            tree[c-1].append(i)

    dp = [set() for _ in range(N)]
    def dfs(i):
        if len(dp[i]) == 0:
            res = {i}
            for child in tree[i]:
                res |= dfs(child) 
            dp[i] = res
        return dp[i]
    for i in range(N):
        dfs(i)

    next(lines)
    for l in lines:
        _, *query = map(int, l.split())
        boxes = set()
        for i in query:
            boxes |= dp[i-1]
        ans = len(boxes) 
        print(ans)


if __name__ == "__main__":
    main()

