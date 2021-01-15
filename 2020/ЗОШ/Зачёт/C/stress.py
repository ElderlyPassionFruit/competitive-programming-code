import os
from random import randint

def get(l, r):
	return randint(l, r)

def gen():
	f = open("input.txt", "w")
	n = get(3, 5)
	k = get(0, 100)
	print(n, k, file = f)
	for i in range(n):
		print(get(1, 5), end = " ", file = f)
	print(file = f)

def main():
	os.system("make c && make stupid")
	for te in range(10**6):
		gen()
		os.system("./c < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break

		print("OK", te)
main()