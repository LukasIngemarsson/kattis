

n = int(input())

factors5 = 0
n_ = n
while n_ > 0:
    n_ //= 5
    factors5 += n_
factors2 = factors5

ans = 1
for i in range(2, n + 1):
    prod = i
    while prod % 5 == 0 and factors5 > 0:
        prod //= 5
        factors5 -= 1
    while prod % 2 == 0 and factors2 > 0:
        prod //= 2
        factors2 -= 1

    ans *= prod
    ans %= 1000

ans = str(ans)
print(ans if n <= 6 else (3 - len(ans)) * '0' + ans)