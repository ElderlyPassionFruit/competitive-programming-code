import os
from random import randrange

def get(l, r):
	return randrange(1, 10**10) % (r - l + 1) + l;

chars = ["a","b", "c", "d", "e", "f"]

strings = []

MAXNUM = 100
MAXLEN = 10

def gen_first():
	s1 = ""
	l1 = get(1, MAXNUM)
	for i in range(l1):
		s1 += chars[get(0, 4)]
	return s1

def gen_str():

	s1 = ""
	l1 = get(1, MAXLEN)
	for i in range(l1):
		s1 += chars[get(0, 4)]
	
	while s1 in strings:
		s1 = ""
		l1 = get(1, MAXLEN)
		for i in range(l1):
			s1 += chars[get(0, 4)]
	strings.append(s1)
	return s1

def gen():
	f = open("input.txt", "w")
	s = gen_first()
	print(s, file = f)

	n = get(1, MAXNUM)
	print(n, file = f)
	for i in range(n):
		print(gen_str(), file = f)

	q = get(1, 1)
	print(q, file = f)
	for i in range(q):
		l = get(1, len(s))
		r = get(l, len(s))
		print(l, r, file = f)


def main():
	for te in range(1000000):
		gen()

		os.system("./a")
		correct = open("output.txt", "r").read();

		os.system("./b")
		incorrect = open("output.txt", "r").read();

		if (correct != incorrect):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("correct")
			print(correct)
			print("incorrect")
			print(incorrect)
			break
		print("OK", te)
main()