import sys
from math import ceil


def main():
    lines = sys.stdin.read().splitlines() 
    for l in lines:
        n = int(l)
        p = n
        stan = False
        while p > 1:
            p = ceil(p / (2 if stan else 9))
            stan = not stan
        print("Stan" if stan else "Ollie", "wins.")


if __name__ == "__main__":
    main()
