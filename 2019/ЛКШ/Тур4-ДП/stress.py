import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

def gen():
	n = get(4, 4)
	k = get(2, 2)
	f = open("input.txt", "w")
	print(n, k, file = f)
	for i in range(2, n + 1):
		u = get(1, i - 1)
		c = get(1, 1)
		print(i, u, c, file = f)

def main():
	for te in range(10**6):
		gen()

		os.system("./b")
		correct = open("output.txt", "r").readline()

		os.system("./a")
		incorrect = open("output.txt", "r").readline()

		if (correct != incorrect):
			print("WA", te)
			print(open("input.txt", "r").read())
			print("correct =", correct)
			print("incorrect =", incorrect)
			break
		print("OK", te)

main()