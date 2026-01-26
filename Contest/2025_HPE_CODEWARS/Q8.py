
a = list(input().split(' '))

stk = []
cur = None

for v in a[::-1]:
    if v == '':
        continue
    try:
        val = float(v)
        stk.append(val)
    except:
        assert len(stk) >= 2
        a = stk.pop()
        b = stk.pop()
        if v == "^":
            v = "**"
        res = float(eval(f"{a}{v}{b}"))
        stk.append(res)

print(f"{stk[0]:.3f}")

