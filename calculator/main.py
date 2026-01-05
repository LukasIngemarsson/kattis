import sys


def main():
    lines = sys.stdin.read().splitlines() 
    for l in lines:
        ans = eval(l)
        print(f"{ans:.2f}")


if __name__ == "__main__":
    main()

