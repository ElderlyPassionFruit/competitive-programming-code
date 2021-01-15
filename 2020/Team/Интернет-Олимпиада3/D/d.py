a = int(input())
b = int(input())
x = a % 9;
ans = 1
for i in range(a, min(a + 9, b + 1)):
	ans *= x
	ans %= 9
	x += 1
	x %= 9
if ans == 0:
	print(9)
else:
	print(ans)