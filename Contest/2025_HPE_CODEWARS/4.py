n = int(input())
lst = []
even_lst = []
max_v = -1
max_band = None
tot = 0
for _ in range(n):
    lst = list(input().split(', '))
    name, val = lst[0], lst[1]
    val = int(val)
    tot += val
    if val % 2 == 0:
        even_lst.append(name)
    if val > max_v:
        max_v = val
        max_band = name

print('TAIWAN BAND DATA ANALYSIS REPORT')
print('============================')
print(f'Total Number of Members: {tot}')
print('----------------------------')
print('List of Even-Member Bands:')
for name in even_lst:
    print('-', name)
print('----------------------------')
print(f'Largest Band: {max_band}, with {max_v} members')
print('----------------------------')
print(f'Average Number of Members: {tot / n:.1f}')
print('============================')

