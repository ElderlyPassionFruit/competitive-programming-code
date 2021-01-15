import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 400)
	print(n, file = f)
	c = ["(", ")"]
	s = ""
	for i in range(n):
		s += c[get(0, len(c) - 1)]
	print(s, file = f)
	for i in range(2, n + 1):
		print(get(1, i - 1), end = " ", file = f)
	print(file = f)

def main():
	os.system("make b && make stupid_b")
	for te in range(10**6):
		gen()
		os.system("./b < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_b < input.txt > output.txt")
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