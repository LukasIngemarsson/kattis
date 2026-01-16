

def main():
    N, t = map(int, input().split())
    A = list(map(int, input().split()))
    
    match t:
        case 1:
            print(7)
        case 2:
            if A[0] > A[1]:
                print("Bigger")
            elif A[0] == A[1]:
                print("Equal")
            else:
                print("Smaller")
        case 3:
            print(sorted(A[:3])[1])
        case 4:
            print(sum(A))
        case 5:
            print(sum(x for x in A if x % 2 == 0))
        case 6:
            print(''.join(chr(97 + x % 26) for x in A))
        case 7:
            i = 0
            seen = set()
            while True:
                seen.add(i)
                i = A[i]
                if i in seen:
                    print("Cyclic")
                    break
                if i < 0 or i >= N:
                    print("Out")
                    break
                elif i == N - 1:
                    print("Done")
                    break


if __name__ == "__main__":
    main()

