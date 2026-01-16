for _ in range(int(input())):
    s=[]
    for _ in range(int(input())):
        c=input()[0]
        if c in"UIA":a,b=s.pop(),s.pop()
        s+=[frozenset()if c=='P'else s[-1]if c=='D'else a|b if c>'I'else a&b if c>'A'else b|{hash(a)}]
        print(len(s[-1]))
    print("***")