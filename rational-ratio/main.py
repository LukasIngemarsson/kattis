import sys

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

f, r = sys.stdin.readlines()[0].strip().split()
r = int(r)
digs, decs = f.split('.')
stat = decs[:-r] # static decimals

totf = (int(digs) * (10 ** len(decs)) + int(decs), 10 ** len(decs))
statf = (int(digs) * (10 ** len(stat)) + int(stat), 10 ** len(stat)) if stat else (int(digs), 1)
num = totf[0] - statf[0]
denom = totf[1] - statf[1]

gcd_ = gcd(num, denom)
num //= gcd_
denom //= gcd_

print(f"{num}/{denom}")
