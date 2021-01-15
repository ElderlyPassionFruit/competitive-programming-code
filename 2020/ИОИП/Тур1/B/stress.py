import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 15)
	print(n, file = f)
	a = []
	for i in range(n):
		x = get(1, 10)
		print(x, end = " ", file = f)
	print(file = f)

def main():
	os.system("make b && make stupid")
	for te in range(10**6):
		gen()
		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt").read()
		os.system("./b < input.txt > output.txt")
		out = open("output.txt").read()
		if int(out) != int(ans):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)

main()