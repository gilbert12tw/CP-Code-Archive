while True:
    try:
        a = list(map(int, input().split()))
        tot, bad = a[0], a[1]
        if tot <= 10000:
            if bad <= tot * 0.02:
                ret = 0
            elif bad <= tot * 0.05:
                ret = bad
            else:
                ret = tot
        else:
            if bad <= tot * 0.04:
                ret = 0
            elif bad <= tot * 0.08:
                ret = bad
            else:
                ret = tot

        print(f"{tot} {bad}")
        print()
        print(f"Return Quantity is {ret} unit{'s' if ret > 0 else ''}")
        print()

    except:
        break

