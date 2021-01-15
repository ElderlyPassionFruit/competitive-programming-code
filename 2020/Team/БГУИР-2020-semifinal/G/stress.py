import os
from random import randint as get

MAX = 100

def gen():
	f = open("input.txt", "w")
	t = get(1, MAX)
	print(t, file = f)
	for i in range(t):
		n = get(1, MAX)
		m = get(1, MAX)
		while (n * m % 4 != 0):
			m += 1
		r = get(1, n)
		c = get(1, m)
		print(n, m, r, c, file = f)

def main():
	os.system("make g")
	for te in range(10**6):
		gen()
		a = os.system("./g < input.txt > output.txt")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		print("OK", te)

main()