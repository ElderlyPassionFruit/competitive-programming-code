import os
from random import randrange

def get(l, r):
	return randrange(1, 10000000) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	n = get(3, 10)
	q = get(1, 100)
	print(n, q, file = f)
	for i in range(2, n + 1):
		a = get(1, i - 1)
		c = get(1, 20)
		print(i, a, c, file = f)
	for i in range(q):
		a = get(1, n)
		b = get(1, n)
		while a == b:
			b = get(1, n)
		print(a, b, file = f)


for te in range(10000000):
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