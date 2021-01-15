def gcd(a, b):
	while (b):
		a %= b;
		a, b = b, a;
	return a;

a = input().split()
x = int(a[0])
y = int(a[1])

g = gcd(x, y)
x //= g
y //= g

# x/y >= 1/a -> a * x >= y -> a > y // x

flag = False;
last = 0
it = 0
while x > 0:
	a = 0
	if flag == False:
		if y % x == 0:
			a = y // x + 1
		else:
			a = (y + x - 1) // x
		flag = True
	else:
		a = (y + x - 1) // x
	if (a <= last):
		a = last + 1
	if (a % 2 == 0):
		a += 1
	last = a
	it += 1
	print(len(str(a)), "it =", it)
	g = gcd(x, y)
	x = x * a // g - 1 * y // g
	y = y * a // g
	g = gcd(x, y)
	x //= g
	y //= g
