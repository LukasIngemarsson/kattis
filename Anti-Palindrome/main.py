

def main():
    s = [c for c in input().lower() if c.isalpha()]

    n = len(s)
    for i in range(1, n):
        if s[i-1] == s[i] or (i < n - 1 and s[i-1] == s[i+1]):
            print("Palindrome")
            return
    print("Anti-palindrome")


if __name__ == "__main__":
    main()
