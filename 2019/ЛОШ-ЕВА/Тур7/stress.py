import os
from random import randrange as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l;

def gen():
	f = open("input.txt", "w")
	x = get(2, 100)
	y = get(2, 100)
	d = get(2, min(x, y))
	g = get(1, 100)
	print(x, y, d, g, file = f)
	for i in range(g):
		a = get(1, x)
		b = get(1, y)
		print(a, b, file = f)

def main():
	for te in range(10000000):
		gen()
		os.system("./a")
		correct = open("output.txt", "r").read()

		os.system("./b")
		incorrect = open("output.txt", "r").read()

		if (correct != incorrect):
			print("WA", te)
			print("input")
			print(open("input.txt", "r").read())
			print("correct")
			print(correct)
			print("incorrect")
			print(incorrect)
			break
		print("OK", te)

main()
