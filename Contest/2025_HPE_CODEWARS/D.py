s = input()

for c in s:
    if 'a' <= c <= 'y':
        c = chr(ord(c) + 1)
    elif c == 'z':
        c = 'a'
    elif 'A' <= c <= 'Y':
        c = chr(ord(c) + 1)
    elif c == 'Z':
        c = 'A'
    print(c, end='')