import sys


def main():
    parts = sys.stdin.read().split("\n\n")
    for p in parts[1:]:
        lines = p.strip().split('\n')
        pref_ranks = [] 
        for l in lines[1:]:
            _, pref = l.split() 
            pref_ranks.append(int(pref)) 
        pref_ranks.sort()
        ans = sum(abs(i + 1 - pref) for i, pref in enumerate(pref_ranks))
        print(ans)


if __name__ == "__main__":
    main()

