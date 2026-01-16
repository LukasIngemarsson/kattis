import sys


def main():
    lines = sys.stdin.read().splitlines()
    T = int(lines[0].split()[1])
    people = [tuple(map(int, l.split())) for l in lines[1:]]
    timesteps = [[] for _ in range(T)]
    for c, t in people:
        timesteps[t].append(c)

    ans = 0
    for t in reversed(range(T)):
        if len(timesteps[t]) == 0:
            continue
        timesteps[t].sort(reverse=True)
        if t > 0:
            while len(timesteps[t]) > 1:
                timesteps[t-1].append(timesteps[t].pop())
        ans += timesteps[t][0]
    print(ans)


if __name__ == "__main__":
    main()

