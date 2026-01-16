from collections import Counter


def main():
    N, t = map(int, input().split())
    A = list(map(int, input().split()))
    
    match t:
        case 1:
            ok = False
            candidates = [x for x in set(A) if x <= 7777]
            M = len(candidates)
            for i in range(M):
                for j in range(i + 1, M):
                    x = candidates[i]
                    y = candidates[j]
                    if x != y and x + y == 7777:
                        ok = True
                        break
                if ok:
                    break
            print("Yes" if ok else "No")
        case 2:
            ok = len(set(A)) == len(A)
            print("Unique" if ok else "Contains duplicate")
        case 3:
            x, cnt = Counter(A).most_common(1)[0]
            print(x if cnt > N / 2 else -1)
        case 4:
            sorted_A = sorted(A)
            if len(A) % 2 == 0:
                print(sorted_A[N//2-1], end=" ")
            print(sorted_A[N//2])
        case 5:
            print(*sorted(x for x in A if 100 <= x <= 999)) 


if __name__ == "__main__":
    main()

