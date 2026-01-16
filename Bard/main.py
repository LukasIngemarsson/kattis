from copy import deepcopy

N = int(input())
E = int(input())

has_heard = [set() for _ in range(N + 1)]
song_cnt = 0
for _ in range(E):
    villagers = list(map(int, input().split()))
    villagers.pop(0)

    if 1 in villagers:
        for v in villagers:
            has_heard[v].add(song_cnt)
        song_cnt += 1
    else:
        tot_heard = set()
        for v in villagers:
            tot_heard = tot_heard | has_heard[v]
        for v in villagers:
            has_heard[v] = deepcopy(tot_heard)

knows_all = sorted([v for v in range(1, N + 1) if len(has_heard[v]) == song_cnt])
print(*knows_all, sep='\n')