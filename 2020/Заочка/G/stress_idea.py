import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l) + l

n = 0
a = []
b = 0

def gen():
	global a, b, n
	n = 1
	while n % 2 == 1:
		n = get(1, 5) * 2
		a = []
		for i in range(n):
			a.append(get(0, 10))
		a.sort()
		fans = []
		for i in a:
			if len(fans) == 0 or i != fans[-1]:
				fans.append(i)
			elif len(fans) > 0:
				fans.remove(i)
		a = fans
		n = len(a)
		b = get(1, 10)

def check(x):
	global a, b
	ans = 0
	for i in a:
		ans = ans ^ (i + x)
	return ans == b

def solve():
	global b
	ans = []
	for x in range(0, 1000):
		if (check(x)):
			ans.append(x)
	return ans

def main():
	global a, b, n
	for te in range(100):
		gen()
		ans = solve()
		if len(ans) == 0:
			print("n =", n, "a =", a, "b =", b, "ans =", ans)


main()