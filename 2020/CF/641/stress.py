import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 30)
	m = get(1, 30)
	q = get(1, 20)
	print(n, m, q, file = f)
	for i in range(n):
		for i in range(m):
			print(get(0, 1), end = "", file = f)
		print(file = f)
	for i in range(q):
		print(get(1, n), get(1, m), get(1, 10), file = f)

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