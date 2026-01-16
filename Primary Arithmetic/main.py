

def main():
    while True:
        a, b = input().split()
        if a == '0' and b == '0':
            break
        a, b = [int(ch) for ch in a], [int(ch) for ch in b]

        prev_had_carry = 0
        carry_cnt = 0
        n = max(len(a), len(b))
        for i in range(n):
            x = prev_had_carry
            if i < len(a):
                x += a[-1-i]
            if i < len(b):
                x += b[-1-i]
            if x > 9:
                carry_cnt += 1
                prev_had_carry = 1
            else:
                prev_had_carry = 0

        print((str(carry_cnt) if carry_cnt > 0 else "No") +" carry operation" +\
                ('s' if carry_cnt > 1 else '') + '.')


if __name__ == "__main__":
    main()

