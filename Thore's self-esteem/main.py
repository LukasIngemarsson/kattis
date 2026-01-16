

n = int(input())
names = [input() for _ in range(n)]

thore_name = "ThoreHusfeldt"
thore_idx = [i for i, name in enumerate(names) if name == thore_name][0]
names = names[:thore_idx]

if thore_idx == 0:
    print("Thore is awesome")
else:
    max_cnt = 0
    for name in names:
        cnt = 0
        for i in range(min(len(name), len(thore_name))):
            if name[i] != thore_name[i]:
                break
            cnt += 1
        max_cnt = max(max_cnt, cnt)
    
    if max_cnt >= len(thore_name) - 1:
        print("Thore sucks")
    else:
        print(thore_name[:max_cnt + 1])
