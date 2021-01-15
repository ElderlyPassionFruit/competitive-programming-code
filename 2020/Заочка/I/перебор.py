def gcd(a, b):
	while b:
		a %= b
		a, b = b, a
	return a

def lcm(a, b):
	return a // gcd(a, b) * b

INF = 0
NEED = 0

def solve(ans, SUM, LCM, LEN):
	if LCM > INF:
		return -1
	if SUM > 300:
		return -1
	if LEN == NEED:
		if ans % LCM == 0:
			return ans
		else:
			return -1

	for i in range(1, 10):
		if (SUM + i) % 5 == 0:
			continue
		x = solve(ans + i * 10 ** LEN, SUM + i, lcm(LCM, SUM + i), LEN + 1)
		if x != -1:
			return x

	return -1

def get_lcm(x):
	s = 0
	ans = 1
	while x:
		s += x % 10
		x //= 10
		ans = lcm(ans, s)
	return ans

def get_sum(x):
	s = 0
	while x:
		s += x % 10
		x //= 10
	return s

def get_len(x):
	ans = 0
	while x:
		ans += 1
		x //= 10
	return ans

x = 44233216123311211121112112
#print(get_sum(1746999831915957933216123311211121112112))
LEN = 50
NEED = LEN
INF = 10 ** 9
print(LEN, solve(x, get_sum(x), get_lcm(x), get_len(x)))
