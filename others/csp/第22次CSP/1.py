def read_strs():
    return input().strip().split()


def read_ints():
    return list(map(int, read_strs()))


def main():
    n, m, L = read_ints()
    mat = []
    for i in range(n):
        line = read_ints()
        mat.append(line)
    h = [0 for _ in range(L+3)]
    for line in (mat):
        for x in line:
            h[x] += 1
    for i in range(0, L):
        if i > 0:
            print(' ', end='')
        print(h[i], end='')

if __name__ == '__main__':
    main()