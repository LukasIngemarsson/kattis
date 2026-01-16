import sys

with sys.stdin as f:
    lines = [l.strip() for l in f.readlines()]

for_to_eng = {}
output = False
for l in lines:
    if output:
        print(for_to_eng.get(l, "eh")) 
    elif l == "":
        output = True
    else:
        a, b = l.split()
        for_to_eng[b] = a