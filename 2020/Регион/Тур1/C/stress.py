import os
from random import randint

def get(l, r):
	return randint(l, r)

def gen():
	f = open("input.txt", "w")
	n = 10000
	m = 72
	q = 10000
	print(n, m, q, file = f)

def main():
	os.system("clear && make c && make c60")
	for te in range(10**6):
		gen()
		os.system("./c < input.txt > output.txt")
		out = open("output.txt", "r").read()
		ans = open("output.txt", "r").read()
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