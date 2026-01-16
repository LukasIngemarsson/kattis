import sys


def main():
    lines = iter(sys.stdin.read().splitlines())
    N = int(next(lines))
    strings = [''] + [next(lines) for _ in range(N)]
    last_a = -1
    next_idx = [-1] * (N + 1)
    tail_idx = list(range(N + 1))
    final_a = 1
    for l in lines:
        a, b = map(int, l.split())
        next_idx[tail_idx[a]] = b
        tail_idx[a] = tail_idx[b]
        final_a = a
    curr = final_a
    while curr != -1:
        sys.stdout.write(strings[curr])
        curr = next_idx[curr]
    sys.stdout.write('\n')


if __name__ == "__main__":
    main()

