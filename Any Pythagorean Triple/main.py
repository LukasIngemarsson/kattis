

def main():
    n = int(input())

    ok = False
    for a in range(1, n):
        for b in range(a, n):
            c = n - a - b
            if c < max(a, b):
                break
            if a**2 + b**2 == c**2:
                print(a, b, c)
                ok = True
                break
        if ok:
            break
    if not ok:
        print(0, 0, 0)


if __name__ == "__main__":
    main()
