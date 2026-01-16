from decimal import Decimal


def main():
    a, b, c, = map(Decimal, input().split())
    print(a * b / c)


if __name__ == "__main__":
    main()

