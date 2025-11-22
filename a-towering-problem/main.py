from itertools import combinations

def main():
    num_boxes = 6

    input_nums = list(map(int, input().strip().split()))
    box_heights = input_nums[:num_boxes]
    tower1_height, _ = input_nums[num_boxes:]

    tower1 = []
    tower2 = []
    for i, j, k in combinations(range(num_boxes), 3):
        if box_heights[i] + box_heights[j] + box_heights[k] == tower1_height:
            idxs = (i, j, k)
            tower1 = sorted((box_heights[i] for i in idxs), reverse=True)
            tower2 = sorted((h for i, h in enumerate(box_heights) if i not in idxs), reverse=True)
            break
    
    print(*tower1, *tower2)


if __name__ == "__main__":
    main()
