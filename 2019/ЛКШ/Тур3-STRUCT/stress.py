import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l;

def gen():
	n = get(2, 10)
	s = get(1, 10)
	m = get(0, 10)
	f = open("input.txt", "w")
	print(n, s, m, file = f)
	for i in range(m):
		c = get(1, s)
		a = get(1, n - 1)
		b = get(a + 1, n)
		print(c, a, b, file = f)

	q = get(1, 10)
	print(q, file = f)
	for i in range(q):
		x = get(1, n - 1)
		y = get(x + 1, n)
		print(x, y, file = f)


def main():
	for te in range(10**6):
		gen()

		os.system("./a.out")
		correct = open("output.txt", "r").readline()
		
		os.system("./a")
		incorrect = open("output.txt", "r").readline()

		if (correct != incorrect):
			print("WA", te)
			print(open("input.txt", "r").read())
			print("correct =", correct)
			print("incorrect =", incorrect)
			break;

		print("OK", te)

main()