S = input()

if S[-1] == 'E':
    print("INVALID")
    exit(0)

for i in range(len(S) - 1):
    if S[i] == 'O' and S[i + 1] == 'O':
        print("INVALID")
        exit(0)

def is_pow_2(x) -> bool:
    return x != 0 and (x & (x - 1)) == 0

def test(X):
    for c in S[::-1]:
        if c == 'O':
            if X - 1 <= 0 or (X - 1) % 3 != 0:
                return -1

            X = (X - 1) // 3
        else:
            X *= 2

        if is_pow_2(X):
            return -1

    return X

X = 1
while True:
    # print(f"test {X}")
    ans = test(X)

    if ans == -1:
        X *= 2
        continue

    print(ans)
    exit(0)
