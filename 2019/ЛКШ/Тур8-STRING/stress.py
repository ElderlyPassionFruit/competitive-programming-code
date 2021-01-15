import os
from random import randrange as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

lett = ["a","b"]

def get_string():
	s = ""
	l = get(1, 3)
	for i in range(l):
		s += lett[get(0, len(lett) - 1)]
	return s

def gen():
	n = len(lett)
	m = get(3, 3)
	p = get(1, 2)
	f = open("input.txt", "w")
	print(n, m, p, file = f)
	print("".join(lett), file = f)
	for i in range(p):
		print(get_string(), file = f)	

def main():
	for te in range(10**6):
		gen()

		os.system("./a")
		correct = open("output.txt", "r").read()

		os.system("./b")
		incorrect = open("output.txt", "r").read()

		if (correct != incorrect):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("correct = ")
			print(correct)
			print("incorrect = ")
			print(incorrect)

			break
		print("OK", te)

main()
