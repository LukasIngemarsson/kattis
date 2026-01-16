import sys


def main():
    D, R, T = map(int, sys.stdin.read().split())

    f = lambda x: x**2 + (1 - D) * x + ((D**2 - D) / 2 - 9 - (R + T))
    ans = next(int(R - (i * (i + 1) / 2 - 6)) for i in range(4, 45) if f(i) == 0)
    print(ans)


if __name__ == "__main__":
    main()

