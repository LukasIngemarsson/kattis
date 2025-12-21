import sys


def main():
    lines = sys.stdin.read().split() 
    N, M = lines
    K = len(M) - 1
    if K < len(N):
        ans = N[:-K] + '.' + N[-K:]
    else:
        ans = '0.' + '0' * (K - len(N)) + N
    ans = ans.rstrip('0').rstrip('.')
    print(ans)


if __name__ == "__main__":
    main()

