import itertools
import math

n = int(input())
ages = list(map(int, input().split()))

for perm in itertools.permutations(ages, n):
    for i in range(1, n):
        if math.gcd(perm[i], perm[i-1]) == 1:
            break
    else:
        print(*perm)
        break
else:
    print("Neibb")