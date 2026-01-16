import sys

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

lines = [l.strip() for l in sys.stdin.readlines()]
for l in lines:
    if l == '0':
        break

    decs = l[2:-3]
    optf = (0, float("inf"))
    for i in range(1, len(decs) + 1):
        stat = decs[:-i] # static decimals
        rep = decs[-i:] # repeating decimals

        totf = (int(decs), 10 ** len(decs))
        statf = (int(stat), 10 ** len(stat)) if stat else (0, 1)
        num = totf[0] - statf[0]
        denom = totf[1] - statf[1]

        gcd_ = gcd(num, denom)
        num //= gcd_
        denom //= gcd_

        if denom < optf[1]:
            optf = (num, denom)
    
    print(*optf, sep='/')