N = int(input())
A = list(map(int, input().split()))

num = 1
LIMIT = 2 ** 200

ans = max(A)

while num <= LIMIT:
    B = []
    
    i = 0
    while i < len(A):
        if i + 1 < len(A) and A[i] == num and A[i + 1] == num:
            B.append(num * 2)
            i += 2
        elif A[i] > num:
            B.append(A[i])
            i += 1
        else:
            i += 1

    if len(B) == 0:
        break

    ans = max(B)
    A = B
    num *= 2

print(ans)
