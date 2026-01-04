import sys


def main():
    lines = sys.stdin.read().splitlines() 

    START = 500
    MAX_DIM = 2 * START + 1
    grid = [[' '] * MAX_DIM for _ in range(MAX_DIM)]
    r, c = START, START
    r_min, r_max = r, r
    c_min, c_max = c, c
    for l in lines:
        if l == "left":
            c -= 1
            c_min = min(c_min, c)
        elif l == "right":
            c += 1
            c_max = max(c_max, c)
        elif l == "up":
            r -= 1
            r_min = min(r_min, r)
        else:
            r += 1
            r_max = max(r_max, r)
        grid[r][c] = '*'
    grid[START][START] = 'S'
    grid[r][c] = 'E'

    width = c_max - c_min + 1
    print('#' * (width + 2))
    for r in range(r_min, r_max + 1):
        print('#' + ''.join(grid[r][c] for c in range(c_min, c_max + 1)) + '#')
    print('#' * (width + 2))


if __name__ == "__main__":
    main()

