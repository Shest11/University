def bubble_sort_items(items):
    n = len(items)
    for i in range(n):
        for j in range(n - i - 1):
            if items[j][1][0] > items[j + 1][1][0]:
                items[j], items[j + 1] = items[j + 1], items[j]
    return items

cl = int(input())
d = {}

for i in range(cl):
    a = input().split()
    d[a[0]] = [int(a[1]), int(a[2])]

items = list(d.items())
items_sort = bubble_sort_items(items)

c = 0
for name, [boys, girls] in items_sort:
    if boys > girls:
        c += 1
        print(name)

print()
print(c)