import sys

lines = [l.strip() for l in sys.stdin.readlines()]
N = int(lines.pop(0))

def is_placeholder(s):
    return s.startswith('<') and s.endswith('>')

for i in range(0, N * 2, 2):
    s1 = lines[i].split()
    s2 = lines[i+1].split()
    seqlen = len(s1)

    if seqlen != len(s2):
        print("-")
        continue

    def run_pass():
        for j in range(seqlen):
            a = s1[j]
            b = s2[j]
            if is_placeholder(a) and not is_placeholder(b):
                for k in range(seqlen):
                    if s1[k] == a:
                        s1[k] = b
                return True
            elif not is_placeholder(a) and is_placeholder(b):
                for k in range(seqlen):
                    if s2[k] == b:
                        s2[k] = a
                return True
        return False

    while (run_pass()):
        pass

    ans = []
    for a, b in zip(s1, s2):
        if is_placeholder(a) and is_placeholder(b): 
            ans.append("arbitrary")
        elif a == b:
            ans.append(a)
        else:
            print("-")
            break
    else:
        print(" ".join(ans))