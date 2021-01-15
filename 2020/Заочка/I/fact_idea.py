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

def fact(x):
	ans = 1
	for i in range(x):
		if ((i + 1) % 5 == 0):
			continue
		ans *= (i + 1)
	return ans


for i in range(1, 54):
	print(fact(i), check(fact(i)))	