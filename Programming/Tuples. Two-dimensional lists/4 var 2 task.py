def get_matrix(x):
    for i in range(n**2):
        a = input().split()
        l = []
        for j in a:
            l.append(int(j))
        x.append(l)
    return x

def check_correct(x):
    for i in x:
        if sorted(i) != correct_list:
             return False
    return True

n = int(input())
row_m = []
square_m = []
column_m = []
correct_list = []
correct = True

for i in range(1, (n**2)+1):
    correct_list.append(i)

get_matrix(row_m)

for big_row in range(n):
    for big_col in range(n):
        l = []
        cnt = 0
        for i in range(big_row * n, (big_row + 1) * n):
            for j in range(big_col * n, (big_col + 1) * n):
                    l.append(row_m[i][j])
        square_m.append(l)

for i in range(n**2):
    l = []
    for j in range(n**2):
        l.append(row_m[j][i])
    column_m.append(l)

if check_correct(row_m) and check_correct(square_m) and check_correct(column_m):
    print("Correct")
else:
    print("Incorrect")