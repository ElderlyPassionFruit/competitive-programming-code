import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10 ** 10) % (r - l + 1) + l

def gen_time():
	h = get(0, 24)
	m = get(0, 60)
	x = h * 60 + m
	h = str(h)
	m = str(m)
	if len(h) == 1:
		h = "0" + h
	if len(m) == 1:
		m = "0" + m
	return x, h + ":" + m

def gen():
	n = get(5, 5)
	f = open("input.txt", "w")
	print(n, file = f)
	s = []
	for i in range(n):
		x, t = gen_time()
		s.append([x, t, get(1, 10), get(1, 10), get(1, 10), get(1, 10)])
	s.sort()
	for i in s:
		print(i[1], i[2], i[3], i[4], i[5], file = f)


def main():
	for te in range(10 ** 6):
		gen()

		os.system("./a")
		correct = open("output.txt", "r").read()

		os.system("./b")
		incorrect = open("output.txt", "r").read()

		if (correct != incorrect):
			print("WA", te)
			print(open("input.txt", "r").read())
			print(correct)
			print(incorrect)
			break
		print("OK", te)


main()