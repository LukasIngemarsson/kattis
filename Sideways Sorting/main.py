

def main():
    first = True
    while True:
        r, c = map(int, input().split())
        if r == 0 and c == 0:
            break
        
        if first:
            first = False
        else:
            print()

        cols = ["" for _ in range(c)]
        for _ in range(r):
            s = input()
            for j in range(c):
                cols[j] += s[j]
        
        cols.sort(key=lambda x: x.lower())

        for i in range(r):
            print(''.join([cols[j][i] for j in range(c)]))


if __name__ == "__main__":
    main()
