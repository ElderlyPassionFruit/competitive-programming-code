MOD = 1


def mul(a, b):
	return a * b % MOD

def binpow(a, n):
	if (n == 0):
		return 1
	if (n % 2 == 1):
		return mul(a, binpow(a, n - 1))
	else:
		return binpow(mul(a, a), n // 2)

def solve(a, n):
	MOD = 2 ** (n + 2)
	return binpow(a, 2 ** n)

s = input().split()

n = int(s[0])
a = int(s[1])
print(solve(a, n))