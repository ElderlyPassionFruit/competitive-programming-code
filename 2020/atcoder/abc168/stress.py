import os
from random import randint as get

MX = 10

def gen():
	f = open("input.txt", "w")
	n = get(1, 10);
	print(n, file = f)
	for i in range(n):
		print(get(-MX, MX), get(-MX, MX), file = f)

def main():
	os.system("make main && make stupid")
	for te in range(10**6):
		gen()
		os.system("./main < input.txt > output.txt")
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
