

s = input()

n = len(s)
ans = ""
for i in range(1, n - 1):
    for j in range(i + 1, n):
        a, b, c = s[:i], s[i:j], s[j:]
        d = s[::-1] + b[::-1] + c[::-1]
        if not ans or d < ans:
            ans = d
print(ans)