import sys
from collections import deque


class Teque:
    def __init__(self):
        self.first = deque([])
        self.second = deque([])

    def _calibrate(self):
        if len(self.first) - len(self.second) >= 2:
            self.second.appendleft(self.first.pop())
        elif len(self.second) - len(self.first) == 1:
            self.first.append(self.second.popleft())

    def push_back(self, x):
        self.second.append(x)
        self._calibrate()

    def push_front(self, x):
        self.first.appendleft(x)
        self._calibrate()

    def push_middle(self, x):
        self.first.append(x)
        self._calibrate()

    def get(self, i):
        mid_idx = len(self.first)
        return self.first[i] if i < mid_idx else self.second[i-mid_idx]


def main():
    lines = iter(sys.stdin.read().splitlines())
    next(lines)

    teque = Teque()
    print_buffer = []
    for l in lines:
        op, x = l.split()
        match op:
            case "push_back":
                teque.push_back(x)
            case "push_front":
                teque.push_front(x)
            case "push_middle":
                teque.push_middle(x)
            case "get":
                i = int(x)
                print_buffer.append(teque.get(i))
    for res in print_buffer:
        sys.stdout.write(res + '\n')


if __name__ == "__main__":
    main()

