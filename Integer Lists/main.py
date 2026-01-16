import sys
from collections import deque


def main():
    lines = iter(sys.stdin.read().splitlines())
    T = int(next(lines))
    for _ in range(T):
        p = next(lines)
        next(lines)
        lst = deque(next(lines)[1:-1].split(','))
        if lst[0] == '':
            lst.popleft()

        valid = True
        rev_flag = False
        for ch in p: 
            if ch == 'R':
                rev_flag = not rev_flag
            else:
                try:
                    if rev_flag:
                        lst.pop()
                    else:
                        lst.popleft()
                except IndexError:
                    valid = False
                    break 
        if rev_flag:
            lst.reverse()
        print(f"[{','.join(lst)}]" if valid else "error")


if __name__ == "__main__":
    main()

