a = input().split(':')
b = input().split(':')
time_a = int(a[0]) * 60 + int(a[1])
time_b = int(b[0]) * 60 + int(b[1]) + 24 * 60
fans = time_b - time_a
m = fans % 60
h = fans // 60
ans = str(m)
if len(ans) == 1:
	ans = "0" + ans
ans = ":" + ans
ans = str(h) + ans
if len(ans) == 4:
	ans = "0" + ans
print(ans)