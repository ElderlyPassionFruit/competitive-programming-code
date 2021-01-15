import os
from random import randrange

def get(l, r):
	return randrange(1, 10000000) % (r - l + 1) + l

def gen():
	n = get(3, 1000)

	f = open("input.txt", "w")
	print(n, file = f)
	s = []
	for i in range(n):
		a = get(1, 10000)
		while a in s:
			a = get(1, 10000)
		s.append(a)
		print(a, file = f)

for te in range(1000000000):
	gen()
	os.system("./a")
	correct = open("output.txt", "r").readline()

	os.system("./b")
	incorrect = open("output.txt", "r").readline()
	#print(correct, incorrect)
	if (correct != incorrect):
		print("WA\t", te)
		print(open("input.txt", "r").read())
		print("incorrect", correct)
		print("correct", incorrect)
		break
	else:
		print("OK\t", te)