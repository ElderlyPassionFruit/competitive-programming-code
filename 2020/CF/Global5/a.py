from math import *
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l;

def main():
	while True:
		n = 10
		l = []
		for i in range(n - 1):
			l.append(get(-10, 10))
		l.append(-sum(l))
		a = l
		m = l.copy()
		
		for i in l:
			i //= 2

		print(m)
		print(l)
		
		flag1 = True
		flag2 = False
		for i in range(n):
			if(int(m[i]) % 2 == 1):
				if m[i] > 0:
					if flag1 == False:
						l[i] += 1
					else:
						l[i] -= 1
					flag1 ^= 1
				else:
					if flag2 == False:
						l[i] += 1
					else:
						l[i] -= 1
					flag2 ^= 1
			l[i] //= 2
		if (sum(l) != 0):
			print(a)
			return
		#print()
		#print(m)
		#print(l)

main()