import sys
from collections import deque


def main():
    FIRST_PAGE = 1
    MAX_NUM = 400 + 1

    lines = deque(sys.stdin.read().splitlines())
    T = int(lines.popleft())
    for _ in range(T):
        S = int(lines.popleft())
        adj = [[] for _ in range(MAX_NUM)]
        ending = [-1] * (MAX_NUM)
        for _ in range(S):
            split_line = lines.popleft().split()
            if len(split_line) == 4:
                begin = int(split_line[0])
                sections = [int(ch) for ch in split_line[1:]]
                adj[begin].extend(sections)
            else:
                page, outcome = int(split_line[0]), split_line[1]
                ending[page] = int(outcome == "favourably")

        dp = [-1] * (MAX_NUM)
        def dfs(cur):
            if ending[cur] != -1:
                return ending[cur]
            if dp[cur] == -1:
                dp[cur] = sum(dfs(nbr) for nbr in adj[cur]) 
            return dp[cur]
        ans = dfs(FIRST_PAGE)
        print(ans)


if __name__ == "__main__":
    main()

