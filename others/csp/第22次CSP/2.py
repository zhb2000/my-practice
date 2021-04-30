def read_strs():
    return input().strip().split()


def read_ints():
    return list(map(int, read_strs()))


n, L, r, t = 0,0,0,0
maxn = 600 + 5
mat = [[0 for j in range(maxn)] for i in range(maxn)]
pre = [[0 for j in range(maxn)] for i in range(maxn)]


def calc_pre():
    for i in range(1,n+1):
        for j in range(1,n+1):
            pre[i][j] = pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+mat[i][j]

def getsum(x1,y1,x2,y2):
    return pre[x2][y2]-pre[x2][y1-1]-pre[x1-1][y2]+pre[x1-1][y1-1]


def print_mat(m):
    for i in range(1,n+1):
        for j in range(1,n+1):
            print(f'{m[i][j]} ', end='')
        print()

def main():
    global n, L, r, t
    n, L, r, t = read_ints()
    for i in range(1, n+1):
        line = read_ints()
        for j in range(1,n+1):
            mat[i][j] = line[j-1]
    calc_pre()
    ans = 0
    for i in range(1,n+1):
        for j in range(1,n+1):
            x1=max(i-r,1)
            y1=max(j-r,1)
            x2=min(i+r,n)
            y2=min(j+r,n)
            sqnum = (x2-x1+1)*(y2-y1+1)
            sm = getsum(x1,y1,x2,y2)
            # print(f'({i},{j}), sum={sm}, num={sqnum}')
            if sm <= t*sqnum:
                ans += 1
    print(ans)
    # print('mat:')
    # print_mat(mat)
    # print('pre:')
    # print_mat(pre)
    


if __name__ == '__main__':
    main()