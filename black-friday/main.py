

def main():
    input()
    nums = [int(ch) for ch in input().split()]

    idxs = [[] for _ in range(6 + 1)]
    for k, elem in enumerate(nums):
        idxs[elem].append(k + 1)
    for k in reversed(range(1, 6 + 1)):
        if len(idxs[k]) == 1:
            print(idxs[k][0])
            break
    else:
        print("none")


if __name__ == "__main__":
    main()
