import re

pattern = r'[A-Z]'
s = re.split(pattern, input())

correct = True
for i in range(len(s)):
    if (len(s[i]) + 1) < 2 or (len(s[i]) + 1) > 4:
        correct = False

if correct:
    print("Yes")
else:
    print("No")

