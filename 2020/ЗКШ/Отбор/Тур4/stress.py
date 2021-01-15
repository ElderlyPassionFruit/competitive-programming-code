import os
from random import randint as get

c = ['1','2','3','4']

def gen():
	f = open("input.txt", "w")
	x = "0."
	l = get(1, 7)
	for i in range(l):
		x += c[get(0, len(c) - 1)]
	print(x, file = f)
	n = get(2, 100)
	print(n, file = f)

def main():
	os.system("make b && make stupid_b")
	for te in range(10 ** 6):
		gen()
		os.system("./stupid_b < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		os.system("./b < input.txt > output.txt")
		out = open("output.txt", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
main()