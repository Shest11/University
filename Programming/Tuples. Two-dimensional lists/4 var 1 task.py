def get_matrix(x):
    for i in range(h):
        a = input()
        l = []
        for j in a:
            l.append(int(j))
        x.append(l)
    return x

w, h = map(int, input().split())
p1, p2, rules = [], [], []

get_matrix(p1)
get_matrix(p2)
answer = p1

a = input()
for j in a:
    rules.append(int(j))

for i in range(h):
    for j in range(w):
        if p1[i][j] == 0 and p2[i][j] == 0:
            answer[i][j] = rules[0]
        elif p1[i][j] == 0 and p2[i][j] == 1:
            answer[i][j] = rules[1]
        elif p1[i][j] == 1 and p2[i][j] == 0:
            answer[i][j] = rules[2]
        else:
            answer[i][j] = rules[3]

for i in answer:
    print(*i)

