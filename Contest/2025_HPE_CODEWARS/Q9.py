
def isok(c):
    return (('a' <= c <= 'z') or ('A' <= c <= 'Z') or ('0' <= c <= '9'))

res = []
s = ''
while True:
    try:
        a = input()
    except:
        break
    for c in a:
        if c == ' ':
            res.append(s)
            s = ''
        elif not isok(c):
            res.append(s)
            res.append(c)
            s = ''
        else:
            s += c
print(' '.join(res[::-1]))
        

