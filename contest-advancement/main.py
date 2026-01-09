import sys


def main():
    lines = iter(sys.stdin.read().splitlines())

    N, K, C = map(int, next(lines).split())
    cnts = [0] * (N + 1)
    to_print = [False] * (N + 1)
    tot_cnt = 0
    ranks = [next(lines).split() for _ in range(N)]
    for i, (_, s) in enumerate(ranks):
        s = int(s)
        if cnts[s] < C:
            to_print[i] = True
            cnts[s] += 1
            tot_cnt += 1
            if tot_cnt == K:
                break
    for i, (t, _) in enumerate(ranks):
        if tot_cnt < K and not to_print[i]:
            to_print[i] = True
            tot_cnt += 1
        if to_print[i]:
            sys.stdout.write(t + '\n')


if __name__ == "__main__":
    main()

