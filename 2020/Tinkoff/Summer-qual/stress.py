import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l

div = [1, 2, 3, 4, 6, 12]

def gen():
	f = open("input.txt", "w")
	n = get(1, 4)
	k = get(0, 10)
	print(n, k, file = f)
	for i in range(n):
		print(get(1, 10), end = " ", file = f)
	print(end = "\n", file = f)


def main():
	for te in range(10**6):
		gen()
		os.system("./good < input.txt > output.txt")
		correct = open("output.txt", "r").read()
		os.system("./bad < input.txt > output.txt")
		incorrect = open("output.txt", "r").read()

		if (correct != incorrect):
			print("WA", te)
			print("input = ")
			print(open("input.txt").read())
			print(correct)
			print(incorrect)
			break
		print("OK", te)
main()