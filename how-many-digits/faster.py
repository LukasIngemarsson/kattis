import sys
from math import log, lgamma


def main():
    lines = sys.stdin.read().splitlines() 

    for l in lines:
        n = int(l)
        ans = int(lgamma(n + 1) / log(10)) + 1
        print(ans)


if __name__ == "__main__":
    main()

