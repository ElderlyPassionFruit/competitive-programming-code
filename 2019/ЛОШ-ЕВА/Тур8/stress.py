import os
from random import randrange as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l;

def gen():
	f = open("input.txt", "w")
	n = get(1, 50)
	m = get(1, 50)
	q = get(1, 20)
	print(n, m, q, file = f)
	for i in range(n):
		print(get(1, m), file = f)
	for i in range(q):
		print(get(n + 1, 100), file = f)

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
