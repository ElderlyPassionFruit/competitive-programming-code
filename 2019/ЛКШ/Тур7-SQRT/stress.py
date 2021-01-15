import os
from random import randrange as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

lett = ['a','b']

def get_string():
	s = ""
	l = get(1, 5)
	for i in range(l):
		s += lett[get(1, len(lett))]
	return s

def gen():
	n = get(1, 3)
	q = 1
	f = open("input.txt", "w")
	print(n, q, file = f)
	for i in range(n):
		s = get_string()
		print(s, file = f)
	for i in range(q):
		l = get(1, n)
		r = get(l, n)
		s = get_string()
		print(l, r, s, file = f)

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
			print("correct = ", correct)
			print("incorrect = ", incorrect)

			break
		print("OK", te)

main()
