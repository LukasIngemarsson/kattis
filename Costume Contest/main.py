

def main():
    N = int(input())

    cnts = {}
    for _ in range(N):
        s = input()

        if s not in cnts:
            cnts[s] = 0
        cnts[s] += 1
    
    min_cnt = min(cnts.values())
    ans = sorted([s for s, cnt in cnts.items() if cnt == min_cnt])
    print(*ans, sep='\n')

if __name__ == "__main__":
    main()
