import os
from random import randint as get

MX = 16

def gen():
	f = open("input.txt", "w")
	n = get(1, MX)
	print(n, file = f)
	for i in range(n):
		print(get(1, 10**18), end = " ", file = f)
	print(file = f)

def main():
	os.system("make e && make stupid_e")
	for te in range(10**6):
		gen()
		os.system("./e < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_e < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("out = ", out)
			print("ans = ", ans)
			break
		print("OK", te)
main()