

n, K = map(int, input().split())

n -= 1
ans = 0
if K < n:
    ans += K
    mults = n // K
    if mults != 1:
        ans += 1
    ans += n - K * mults
else:
    ans = n

print(ans)
    