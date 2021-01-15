import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	p = get(1, 10)
	q = get(2, 10)
	a = get(1, 10)
	b = get(1, 10)
	n = get(1, 10)
	print(1, file = f)
	print(p, q, a, b, n, file = f)

def main():
	os.system("make h && make brother")
	for te in range(10**6):
		gen()
		os.system("./h < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		os.system("./brother < input.txt > output.txt")
		out = open("output.txt", "r").read()

		if ans != out:
			print("WA", te)
			print("input =")
			print(open("input.txt", "r").read())
			print("ans =", ans)
			print("out =", out)
			break;
		print("OK", te)

main()
