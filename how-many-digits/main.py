import sys
from math import log10


def main():
    lines = sys.stdin.read().splitlines() 

    MAX_N = 10**7
    digits = [1.0] * (MAX_N + 1)
    for i in range(2, MAX_N + 1):
        digits[i] = digits[i-1] + log10(i)
    digits = [int(x) for x in digits]

    for l in lines:
        n = int(l)
        print(digits[n])


if __name__ == "__main__":
    main()

