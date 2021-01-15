import os
from random import randint as get

MX = 50

def gen():
	f = open("in", "w")
	print(1, file = f)
	n = get(1, MX)
	k = get(1, n)
	print(n, k, file = f)
	for i in range(n):
		print(get(-MX, MX), end = " ", file = f)
	print(file = f)
	for i in range(k - 1):
		x = get(1, n - (k - 1 - i))
		n -= x
		print(x, end = " ", file = f)
	print(n, file = f)

def main():
	os.system("make c && make badC")
	for te in range(10**6):
		gen()
		os.system("./c < in > out")
		out = open("out", "r").read()
		os.system("./badC < in > out")
		ans = open("out", "r").read()
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans = ")
			print(ans)
			print("out = ")
			print(out)
			break
		print("OK", te)
main()
