a = int(input())
d = {}

for i in range(a):
    k = input().split()
    if k[0] in d:
        d[k[0]] += int(k[1])
    else:
        d[k[0]] = int(k[1])

for name in sorted(d.keys()):
    print(name, d[name])