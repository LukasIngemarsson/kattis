from math import log2, floor


def main():
    N = int(input())
    longest = floor(log2(N)) + 1
    seq = [2**i for i in range(longest)]

    print(longest)
    print(*seq)


if __name__ == "__main__":
    main()

