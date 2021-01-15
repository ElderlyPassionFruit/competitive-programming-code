import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l

lett = ["Q", "C"]

def gen():
	f = open("input.txt", "w")
	n = get(2, 5)
	print(n, file = f)
	for i in range(n):
		print(get(0, 5), end = " ", file = f)
	print(end = "\n", file = f)
	q = get(2, 5)
	print(q, file = f)
	for i in range(q):
		t = lett[get(0, 1)]
		if t == "C":
			print(t, get(1, n), get(0, 5), file = f)
		else:
			x1 = get(1, n - 1)
			y1 = get(1, 4)
			x2 = get(x1 + 1, n)
			y2 = get(y1 + 1, 5)
			print(t, x1, y1, x2, y2, file = f)

def main():
	os.system("g++ -std=c++11 -o good stupid_c.cpp")
	os.system("g++ -std=c++11 -o bad c.cpp")
	for te in range(10**6):
		gen()

		os.system("./good < input.txt > output.txt")
		correct = open("output.txt", "r").read()

		os.system("./bad < input.txt > output.txt")
		incorrect = open("output.txt", "r").read()

		if (correct != incorrect):
			print("WA", te)
			print(open("input.txt", "r").read())
			print("correct = ")
			print(correct)
			print("incorrect = ")
			print(incorrect)
			break
		print("OK", te)
main()