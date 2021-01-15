import os
from random import randrange
from time import sleep
def get(l, r):
	return randrange(1, 10000000) % (r - l + 1) + l

def gen():
	n = get(2, 100)
	m = get(1, 100)
	g = get(1, 100)
	s = get(1, 100)
	f = open("input.txt", "w")
	print(n, m, g, s, file = f)
	for i in range(m):
		u = get(1, n)
		v = get(1, n)
		while u == v:
			v = get(1, n)
		g1 = get(1, 100)
		s1 = get(1, 100)
		print(u, v, g1, s1, file = f)

for te in range(1000000000):
	gen()
	os.system("./a")
	correct = open("output.txt", "r").read()

	os.system("./b")
	incorrect = open("output.txt", "r").read()

	if (correct != incorrect):
		print("WA\t", te)
		print(open("input.txt", "r").read())

		print("correct", correct)
		print("incorrect", incorrect)
		
		break
	else:
		print("OK\t", te)