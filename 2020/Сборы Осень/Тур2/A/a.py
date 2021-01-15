s = input().split();
a = int(s[0])
b = int(s[1])
c = int(s[2])
x = int(s[3])
k = int(s[4])

cost = x // k

if cost < a or cost > b:
	print(cost)
else:
	l = a - 1
	r = b + 1
	while l < r - 1:
		mid = (l + r) // 2
		if mid * k * (c + 100) <= x * 100:
			l = mid
		else:
			r = mid
	print(l)