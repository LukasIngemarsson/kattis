import sys
from math import ceil


def main():
    char_iter = iter(sys.stdin.read().split())
    next(char_iter)
    k = int(next(char_iter))

    MAX_TIME = 10**6 + 1
    inc = [0] * MAX_TIME
    dec = [0] * MAX_TIME
    for ch in char_iter:
        t = int(ch)
        inc[t] += 1
        if t + 1000 <= MAX_TIME:
            dec[t+1000] += 1

    ans = 1
    cnt = 0
    for t in range(MAX_TIME):
        cnt -= dec[t]
        cnt += inc[t] 
        ans = max(ans, ceil(cnt / k))
    print(ans)


if __name__ == "__main__":
    main()

