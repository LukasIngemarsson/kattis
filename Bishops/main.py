

def main():
    while True:
        try:
            N = int(input())
            print(2 * (N - 1) if N > 1 else N)
        except: 
            break

if __name__ == "__main__":
    main()
