import sys


def main():
    lines = iter(sys.stdin.read().splitlines())
    next(lines)
    prefs = [tuple(map(int, l.split())) for l in lines]

    prefs.sort(key=lambda t: t[1])
    ans = 0
    while prefs:
        _, U = prefs[0]
        prefs = [p for p in prefs if not p[0] <= U]
        ans += 1
    print(ans)


if __name__ == "__main__":
    main()

