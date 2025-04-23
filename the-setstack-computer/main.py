import sys
from collections import deque

lines = deque([l.strip() for l in sys.stdin.readlines()])

T = int(lines.popleft())
for t in range(T):
    N = int(lines.popleft())
    st = []
    for i in range(N):
        s = lines.popleft()
        if (s == "PUSH"):
            st.append(frozenset())
        elif (s == "DUP"):
            st.append(st[-1])
        else:
            a = st.pop()
            b = st.pop()
            if (s == "UNION"):
                st.append(a | b)
            elif (s == "INTERSECT"):
                st.append(a & b)
            elif (s == "ADD"):
                st.append(b | {hash(a)})
        print(len(st[-1]))
    print("***")