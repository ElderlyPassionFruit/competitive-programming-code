import os
from random import randint

def get(l, r):
	return randint(l, r)

def gen():
	f = open("input.txt", "w")
	n = get(1, 2)
	q = get(1, 2)
	print(n, q, file = f)
	for i in range(n):
		print(get(1, 2), end = " ", file = f)
	print(end = "\n", file = f)

	for i in range(q):
		t = get(1, 2)
		if t == 1:
			print(t, get(1, 2), file = f)
		else:
			l = get(1, n)
			r = get(l, n)
			val = get(1, 2)
			print(t, l, r, val, file = f)

def main():
	os.system("make d && make dy")
	for te in range(10**6):
		gen()
		os.system("./d < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		os.system("./dy < input.txt > output.txt")
		out = open("output.txt", "r").read()
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ")
			print(ans)
			print("out = ")
			print(out)
			break
		print("OK", te)


main()