t = int(input())

mul = [0, 9, 4, 9, 4, 1, 4, 9, 4, 9]

for te in range(t):
	n = int(input())
	while True:
		x = n
		if n % 2 == 0:
			n += (n % 10) * mul[n % 10]
		else:
			n += (n % 10) * mul[n % 10]
		n //= 10
		if (x == n):
			break
	print(n)