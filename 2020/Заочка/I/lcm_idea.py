def gcd(a, b):
	while b:
		a %= b
		a, b = b, a
	return a

def lcm(a, b):
	return a * b // gcd(a, b)

INF = 10**12

a = []

for i in range(3, 10):
	a.append((i, i, i))

for i in range(20):
	b = []
	x = 10**(i + 1)
	for j in a:
		for k in range(3, 10):
			nxt_val = j[0] + k * x
			nxt_sum = j[1] + k
			nxt_lcm = lcm(j[2], nxt_sum)
			if nxt_lcm > INF:
				break
			b.append((nxt_val, nxt_sum, nxt_lcm))
		if len(b) > 10**8:
			break
	a = b
	print(len(a))
	good = []
	for i in a:
		if (i[0] % i[2] == 0):
			good.append(i[0])
	good.sort()
	print(good)