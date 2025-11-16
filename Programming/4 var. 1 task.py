p = input()
v = input()
cb = 0
cc = 0

for i in range(4):
    if p[i]==v[i]:
        cb += 1

for i in p:
    for j in v:
        if i==j:
            cc += 1

print(cb, cc-cb)