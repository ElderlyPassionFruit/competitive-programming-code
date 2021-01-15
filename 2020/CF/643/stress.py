import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 100)
	a = get(1, 10)
	b = get(1, 10)
	c = get(1, 10)
	print(n, a, b, c, file = f)
	for i in range(n):
		print(get(1, 100), end = " ", file = f)
	print(file = f)

def main():
	os.system("make e && make stupid")
	for te in range(10**6):
		gen()
		os.system("./e < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid < input.txt > output.txt")
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