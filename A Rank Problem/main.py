import sys


def main():
    lines = iter(sys.stdin.read().splitlines())
    N, M = map(int, next(lines).split())
    ranking = ['T' + str(i) for i in range(1, N + 1)]
    for _ in range(M):
        a, b = next(lines).split() 
        a_rank = next(i for i, t in enumerate(ranking) if t == a)
        b_rank = next(i for i, t in enumerate(ranking) if t == b)
        if a_rank > b_rank:
            ranking.insert(a_rank + 1, b)
            del ranking[b_rank]
    print(*ranking)


if __name__ == "__main__":
    main()

