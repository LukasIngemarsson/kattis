

def main():
    n = int(input())
    
    cnts = {}
    for _ in range(10 * n):
        vals = map(int, input().split())
        for v in vals:
            if v not in cnts:
                cnts[v] = 0
            cnts[v] += 1
        
    ans = []
    for v, cnt in cnts.items(): 
        if cnt > 2 * n:
            ans.append(v)
    
    if not ans:
        print(-1)
    else:
        ans.sort()
        print(*ans, sep=' ')

if __name__ == "__main__":
    main()
