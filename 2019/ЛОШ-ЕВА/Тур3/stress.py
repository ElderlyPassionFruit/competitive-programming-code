import os
from random import randrange

def get(l, r):
	return randrange(1, 10000000) % (r - l + 1) + l

def gen():
	n = get(3, 3)
	f = open("input.txt", "w")
	print(n, 2, file = f)
	s = []
	for i in range(n):
		s.append(str(get(1, 10)))
	print(" ".join(s), file = f)

for te in range(1000000000):
	
	gen()
	os.system("./a")
	correct = open("output.txt", "r").read()

	if (correct == ""):
		continue;

	os.system("./b")
	incorrect = open("output.txt", "r").read()

	if (correct != incorrect):
		print("WA\t", te)
		print(open("input.txt", "r").read())

		print("correct", correct)
		print("incorrect", incorrect)
		
		break
	else:
		print("OK\t", te)