import itertools

def search(n: int, clauses: list[list[tuple[int, bool]]]) -> bool:
    for bits in itertools.product([0, 1], repeat=n):
        for cl in clauses:
            for idx, is_pos in cl:
                if bits[idx] == is_pos:
                    break
            else:
                break
        else:
            return True
    return False


def main():
    t = int(input())
    for _ in range(t):
        n, m = map(int, input().split())

        clauses = []
        for _ in range(m):
            vars = input().split(" v ")
            cl = []
            for cond in vars:
                is_pos = cond[0] == 'X'
                idx = int(cond[(1 if is_pos else 2):]) - 1
                cl.append((idx, is_pos))
            clauses.append(cl)

        print(("" if search(n, clauses) else "un") + "satisfiable")


if __name__ == "__main__":
    main()
 