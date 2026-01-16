import sys


def main():
    lines = iter(sys.stdin.read().splitlines())
    N, _ = map(int, next(lines).split())
    team_scores = [[0, 0] for i in range(N + 1)]
    greater = set()
    for l in lines:
        t, p = map(int, l.split())
        team_scores[t][0] -= 1
        team_scores[t][1] += p
        if t == 1:
            to_remove = []
            for t in greater:
                if team_scores[t] >= team_scores[1]:
                    to_remove.append(t)
            for t in to_remove:
                greater.remove(t)
        elif team_scores[t] < team_scores[1]:
            greater.add(t)
        print(len(greater) + 1)


if __name__ == "__main__":
    main()

