import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

def gen():
	n = get(20, 25)
	f = open("input.txt", "w")
	print(n, file = f)
	s = []
	for i in range(n):
		s.append([])
		for j in range(n):
			s[-1].append(-1)

	for i in range(n):
		for j in range(n):
			if i == j:
				s[i][j] = 0
			elif s[i][j] == -1:
				s[i][j] = get(0, 1)
				s[j][i] = s[i][j]

	for i in s:
		for j in i:
			print(j, end = " ", file = f)
		print(end = "\n", file = f)

def main():
	for te in range(10**6):
		gen()

		os.system("./a")
		correct = open("output.txt", "r").readline()

		os.system("./b")
		incorrect = open("output.txt", "r").readline()

		if (correct != incorrect):
			print("WA", te)
			print(open("input.txt", "r").read())
			print("correct =", correct)
			print("incorrect =", incorrect)
			break
		print("OK", te)

main()