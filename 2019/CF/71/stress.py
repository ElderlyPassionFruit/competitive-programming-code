import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	n = rnd(2, 5)
	m = rnd(2, 5)
	print(n, m, file = f)
	for i in range(n):
		for j in range(m):
			print(get(0, 1), end = " ", file = f)
		print(end = "\n", file = f)

def main():
	for te in range(10**6):
		gen()

		os.system("./good < input.txt > output.txt")
		correct = open("output.txt", "r").readline()
		
		os.system("./bad < input.txt > output.txt")
		incorrect = open("output.txt", "r").readline()

		if (incorrect != correct and (incorrect == "-1" or correct == "-1")):
			print("WA", te)
			print(open("input.txt", "r").read())
			print("correct = ")
			print(correct)
			print("incorrect = ")
			print(incorrect)
			break
		print("OK", te)


main()