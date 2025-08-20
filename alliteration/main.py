from collections import defaultdict

def main():
    n = int(input())
    for _ in range(n):
        let_to_cnt = defaultdict(int)
        words = input().strip().split()
        for w in words:
            let_to_cnt[w[0]] += 1

        ans = sorted(let_to_cnt.items(), key=lambda x: (x[1], -ord(x[0])))[-1][0]
        print(ans)


if __name__ == "__main__":
    main()
