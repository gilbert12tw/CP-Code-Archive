
a = list(eval(input()))

n = len(a)
m = len(a[0])
mx = 0
tmp = 0

def dfs(x, y):
    global tmp 
    if a[x][y] == 'X':
        return
    a[x][y] = 'X'
    tmp += 1

    if x + 1 < n:
        dfs(x + 1, y)
    if x - 1 >= 0:
        dfs(x - 1, y)
    if y + 1 < m:
        dfs(x, y + 1)
    if y - 1 >= 0:
        dfs(x, y - 1)

cnt = 0
for i in range(n):
    for j in range(m):
        if a[i][j] == 'O':
            tmp = 0
            cnt += 1
            dfs(i, j)
            mx = max(mx, tmp)

print(cnt)
print(mx)
