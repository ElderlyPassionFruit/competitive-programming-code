def get(x):
	a = []
	i = 2
	while i * i <= x:
		if x % i == 0:
			a.append(i)
			if (i * i != x):
				a.append(x // i)
		i += 1
	a.sort()
	return a

def get_d():
	n = 864864
	print(get(n))
	a = get(n)
	last = 0
	print(a[0], end = '')
	for i in range(1, len(a)):
		if (a[i] > 100):
			break
		print(a[i] - a[i - 1], end = '')

	print()


#get_d()


def get_len(x):
	ans = 0
	while x:
		ans += 1
		x //= 10
	return ans

def check(x):
	Sum = 0
	s = x
	while s:
		if s % 10 == 0:
			return False
		Sum += s % 10
		s //= 10
		if x % Sum != 0:
			return False
	return True

def gcd(a, b):
	while b:
		a %= b
		a, b = b, a
	return a

def lcm(a, b):
	return a * b // gcd(a, b)

def get_need(x):
	a = 1
	s = 0
	while x:
		s += x % 10
		x //= 10
		a = lcm(a, s)
	return a

def such_a_smart_solve():
	a = "21121112111223"
	a = a[::-1]
	a = int(a)
	print(get_need(a))
	#return
	h = get_need(a)

	for i in range(1, 10**8):
		x = a + get_len(a) * i
		if (check(x)):
			print(x)

#such_a_smart_solve() 

d = [2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 18, 21, 22, 24, 26, 27, 28, 32, 33, 36, 39, 42, 44, 48, 52, 54, 56, 63, 66, 72, 77, 78, 84, 88, 91, 96, 99, 104, 108, 112, 117, 126, 132]
a = 864864

def check_five(x):
	fans = [0, 0, 0, 0, 0]
	s = 0
	while (x):
		s += x % 10
		x //= 10
		fans[s % 5] = 1
	for i in fans:
		if i == 0:
			return False
	return True

def find(ans, pos, pos_d):
	global d, a
	if (pos == -1):
		if (check(ans)):
			return ans
		else:
			return -1
	if pos_d + 1 < pos:
		return -1
	#if (ans % a >= 10 ** (pos + 1)):
	#	return -1
	if check_five(ans):
		return -1

	if pos == 0:
		for i in range(0, pos_d):
			if (d[i] > 9):
				break
			num = ans + d[i]
			x = find(num, pos - 1, i)
			if x != -1:
				return x
		return -1

	#print(ans, pos, pos_d, ans % a, 10 ** pos)
	for i in range(pos_d - 1, -1, -1):
		if (d[pos_d] - d[i] > 9):
			break
		num = (d[pos_d] - d[i]) * (10 ** (pos)) + ans
		x = find(num, pos - 1, i)
		if x != -1:
			return x
	return -1

def get_lcm(r):
	ans = 1
	for i in range(r):
		ans = lcm(ans, d[i])
	return ans

def solve():
	global d, a
	for pos in range(30, 40):
		a = get_lcm(pos + 1)
		#print("a =", a)
		for l in range(1, pos - 5):
			num = (d[pos] - d[pos - 1]) * (10 ** (l - 1))
			print(pos, l, find(num, l - 2, pos - 1)) 
solve()