import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	k = get(1, 10)
	print(n, k, file = f)
	for i in range(n):
		l = get(1, k)
		r = get(l, k)
		cost = get(1, 10)
		print(l, r, cost, file = f)

def main():
	os.system("make c && make stupid_solve")
	for te in range(10**6):
		gen()
		os.system("./c < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_solve < input.txt > output.txt")
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