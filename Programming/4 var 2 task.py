s = input()
c = 0

for i in range(len(s) - 4):
    if s[i]+s[i+1]+s[i+2]+s[i+3]+s[i+4] == ">>-->" or s[i]+s[i+1]+s[i+2]+s[i+3]+s[i+4] == "<--<<":
        c += 1

print(c)