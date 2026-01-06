import sys


def main():
    lines = iter(sys.stdin.read().splitlines())
    N = int(next(lines))
    truck_x, truck_y = [], []
    for l in lines:
        x, y = map(int, l.split())
        truck_x.append(x)
        truck_y.append(y)

    ans = 0
    for dim in (truck_x, truck_y):
        dim.sort()
        sums = []
        s = 0
        for d in reversed(dim):
            s += d
            sums.append(s)
        sums.pop()
        sums.reverse()
        dim.pop()
        for j, d in enumerate(dim):
            ans += sums[j] - (N - j - 1) * d
    print(ans)


if __name__ == "__main__":
    main()

