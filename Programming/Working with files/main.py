f = open('roles.txt', 'r', encoding='utf-8').read()

d = {}
cnt = 0
index = 0
f1 = f.split('\n')

for line in f1:
    cnt += 1
    if line == 'roles:':
        continue
    if line == 'textLines:':
        index = cnt
        break
    if line[-1]=='.':
        correct_line = line[:-1]
        d[correct_line] = []
    else:
        d[line] = []

current_person = None
number = 0

for line in f1[index:]:
    number += 1
    if ': ' in line:
        name, text = line.split(': ', 1)
        if name in d:
            current_person = name
            if '   ' in line and len(text) > 4:
                d[current_person].append((f'{number})', text[4:]))
            elif '   ' in line and len(text) <= 4:
                continue
            else:
                d[name].append((f'{number})', text))
        else:
            d[current_person].append((f'{number})', line[5:]))
    elif ':' in line and '     ' not in line:
        name, text = line.split(':', 1)
        current_person = name
    else:
        d[current_person].append((f'{number})', line[5:]))

print(d)
for name in d:
    print(f"{name}:")
    for i in d[name]:
        print(*i)
    print()