

t = int(input())

for _ in range(t):
    n = int(input())

    tel_nums = [input() for _ in range(n)]
    tel_nums.sort()

    valid = True
    for i in range(1, n):
        if tel_nums[i].startswith(tel_nums[i-1]):
            valid = False
            break

    print("YES" if valid else "NO")
