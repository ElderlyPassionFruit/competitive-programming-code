import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

lett = ['']

def get_s(l):
	s = ""
	for i in range(l):
		s += chr(get(0, 25) + 65)
	return s 


def gen():
	f = open("input.txt", "w")
	n = 100
	print(n, file = f)
	for i in range(n):
		print(get_s(10), end = " ", file = f)
	print(end = "\n", file = f)

def main():
	for te in range(10**6):
		gen()

		os.system("./good<input.txt>output.txt")
		correct = open("output.txt", "r").readline()

		os.system("./bad<input.txt>output.txt")
		incorrect = open("output.txt", "r").readline()

		if (correct != incorrect):
			print("WA", te)
			print(open("input.txt", "r").read())
			print(correct)
			print(incorrect)
			break
		print("OK", te)

main()