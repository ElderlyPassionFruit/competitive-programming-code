def get(x):
	a = []
	i = 2
	while i * i <= x:
		while (x % i == 0):
			x //= i
			a.append(i)
		i += 1
	if (x > 1):
		a.append(x)
	return a

def solve(n):
	s = 0
	while n:
		s += n % 10
		n //= 10
		print(s, get(s))

def reverse(n):
	n = str(n)
	n = n[::-1]
	n = int(n)
	return n

n = int(input())
#n = reverse(n)
print(n)
solve(n)