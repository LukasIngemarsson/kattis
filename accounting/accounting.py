# brute force, too slow
first_line = input().split(" ")
N = int(first_line[0])
Q = int(first_line[1])
accounts = []

def set_accounts(x):
    for i in range(0, N):
        accounts[i] = x

for i in range(0, N):
    accounts.append(0)
    
for i in range(0, Q):
    line = input().split(" ")
    if (line[0] == "SET"):
        accounts[int(line[1])-1] = int(line[2])

    elif (line[0] == "RESTART"): 
        set_accounts(int(line[1]))

    elif(line[0] == "PRINT"):
        print(accounts[int(line[1])-1])