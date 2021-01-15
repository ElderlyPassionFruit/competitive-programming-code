import os
from random import randrange as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l;

L = ["a","b","c","d"]

def gen():
	f = open("input.txt", "w")
	n = get(2, 10)
	s = ""
	for i in range(n):
		s += L[get(0, 3)]
	print(s, file = f)

def main():
	for te in range(1000000):
		gen()

		os.system("./a")
		crr = open("output.txt", "r").read()

		os.system("./b")
		inc = open("output.txt", "r").read()

		if crr != inc:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("correct =", inc)
			print("incorre =", crr)
			break
		print("OK", te)

main()