n = int(input())
ans = []
while n > 0:
    now = 1
    while now * 10 + 1 <= n:
        now = now * 10 + 1
    ans.append(now)
    n -= now
print(len(ans))
for i in ans:
    print(i, end = ' ')
print()