from collections import deque

def main():
    T = int(input())

    for _ in range(T):
        n = int(input())

        q = deque(range(n))
        ans = [-1 for _ in range(n)]
        for i in range(1, n + 1):
            for _ in range(i):
                q.append(q.popleft())
            ans[q.popleft()] = i

        print(*ans, sep=' ')

if __name__ == "__main__":
    main()
