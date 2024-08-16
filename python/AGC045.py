
class Xbasis:
    def __init__(self):
        self.d = 64
        self.basis = [0] * self.d

    def add(self, msk):
        for i in range(self.d, -1, -1):
            if ((msk>>i)&1) == 0:
                continue
            if (self.basis[i] != 0):
                msk ^= self.basis[i]
            else:
                self.basis[i] = msk
                return True
        return False


def sol():
    n = int(input())
    a = list(map(int, input().split()))
    s = input()

    basis = Xbasis()
    for i in range(n - 1, -1, -1):
        if s[i] == '0':
            # print("a[i] = ", a[i])
            basis.add(a[i])
        else:
            if basis.add(a[i]):
                print(1)
                return
    print(0) 
        



T = int(input())
for _ in range(T):
    sol()
