A = list(map(int, input().split()))
X, Y = map(int, input().split())

S = 0

for i in range(0, len(A), 2):
    S += A[i] * A[i + 1]

S = S // 5

S = S * X // Y

print(S)
