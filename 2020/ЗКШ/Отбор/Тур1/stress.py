import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l) + l

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	m = get(1, 10)
	k = get(1, 10)
	print(n, m, k, file = f)

def main():
	os.system("make c && make stupid_c")
	for te in range(10**6):
		gen()
		os.system("./c < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_c < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (ans != out):
			print("WA", te)
			print("input =")
			print(open("input.txt", "r").read())
			print("ans =", ans)
			print("out =", out)
			break
		print("OK", te)


main()