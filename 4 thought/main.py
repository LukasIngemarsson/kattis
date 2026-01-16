import sys

def main():
    m = int(input())

    ops = ["+", "-", "*", "//"]
    sols = {}
    for i in range(4):
        for j in range(4):
            for k in range(4):
                s = f"4 {ops[i]} 4 {ops[j]} 4 {ops[k]} 4"
                sols[eval(s)] = s.replace("//", "/")

    for _ in range(m):
        n = int(input())
        if n not in sols:
            print("no solution")
        else:
            print(sols[n], "=", n)

if __name__ == "__main__":
    main()
