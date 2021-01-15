import numpy
mod = 0
MOD = 0


def mul(a, b):
	global mod
	global MOD
	n1 = len(a)
	m1 = len(a[0])
	k1 = len(b[0])

	c = [[0 for i in range(k1)] for j in range(n1)]
	#for i in range(n1):
	#	c.append([])
	#	for j in range(k1):
	#		c[-1].append(0)

	res = np.dot(np.array(a), np.array(b))
	for i in range(n1):
		for j in range(k1):
			res[i][j] %= MOD;
	return res;
	for i in range(n1):
		for j in range(k1):
			for t in range(m1):
				c[i][j] += a[i][t] * b[t][j]
				if (c[i][j] > mod):
					c[i][j] -= mod
			c[i][j] %= MOD
	return c


def fastpow(a, n):
	global MOD
	if (n == 0):
		x = []
		for i in range(len(a)):
			x.append([])
			for j in range(len(a)):
				x[-1].append(0)
				if (i == j):
					x[-1][-1] = 1
		return x
	if (n % 2 == 0):
		x = fastpow(a, n // 2)
		return mul(x, x)
	else:
		x = fastpow(a, n - 1)
		return mul(a, x)

def check(a, b, m):
	for i in range(1, m):
		cnt = 0
		cnt += ((a >> i) & 1)
		cnt += ((a >> (i - 1)) & 1)
		cnt += ((b >> i) & 1)
		cnt += ((b >> (i - 1)) & 1)
		if (cnt == 4):
			return False
		if (cnt == 0):
			return False
	return True


def main():
	global MOD, mod
	a = input().split()

	n = int(a[0])
	m = int(a[1])
	MOD = int(a[2])
	mod = MOD*MOD
	M = 1 << m;
	matrix = []
	for i in range(M):
		matrix.append([])
		for j in range(M):
			matrix[-1].append(0)

	for i in range(M):
		for j in range(M):
			x = check(i, j, m)
			if (x == True):
				matrix[i][j] = 1

	matrix = fastpow(matrix, n - 1)

	base = []
	for i in range(M):
		base.append([1])

	fans = mul(matrix, base)

	ans = 0
	for i in range(M):
		ans += fans[i][0]
	ans %= MOD

	print(ans)


main()












