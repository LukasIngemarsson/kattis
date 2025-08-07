

def main():
    while True:
        d, N = input().split()
        d, N = float(d), int(N)
        if d == 0 and N == 0:
            break

        sour = set()
        hives = [tuple(map(float, input().split())) for _ in range(N)]
        for i in range(N):
            x1, y1 = hives[i]
            for j in range(i + 1, N):
                x2, y2 = hives[j]
                if ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5 <= d:
                    sour.add(i)
                    sour.add(j)

        print(f"{len(sour)} sour, {N - len(sour)} sweet")


if __name__ == "__main__":
    main()
