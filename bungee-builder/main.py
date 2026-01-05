

def main():
    N = int(input())
    mountains = list(map(int, input().split()))

    ans = 0
    i = 0
    while i < N - 2:
        if mountains[i] < mountains[i+1]:
            i += 1
            continue
        min_h = mountains[i+1]
        for j in range(i + 2, N):
            dist = min(mountains[i], mountains[j]) - min_h
            ans = max(ans, dist)
            if mountains[i] <= mountains[j]:
                i = j
                break
            min_h = min(min_h, mountains[j])
        else:
            break
    print(ans)


if __name__ == "__main__":
    main()

