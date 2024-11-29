import sys

with sys.stdin as f:
    h = int(f.readline().strip())
    calc_num_cards = lambda x: 2 * x + 3 * (x - 1) * x // 2
    while calc_num_cards(h) % 4 != 0:
        h += 1
    print(h)

# pattern of acceptable heights: starts at 5, then alternates between adding 3 and 5, as follows:
# 5, 8, 13, 16, 21, 24, 29, 32, ...
# although, not needed to solve the problem