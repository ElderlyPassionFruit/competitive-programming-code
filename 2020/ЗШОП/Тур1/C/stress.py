import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(2, 10)
	m = n - 1
	q = get(1, n)
	print(n, m, q, file = f)
	for i in range(2, n + 1):
		print(i, get(1, i - 1), file = f)
	a = []
	for i in range(q):
		x = get(1, n)
		while x in a:
			x = get(1, n)
		a.append(x)
		print(x, file = f)


def main():
	os.system("make c && make smart_c && make gen")
	for te in range(10**6):
		#gen()
		os.system("./gen > input.txt")
		os.system("./c < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		os.system("./smart_c < input.txt > output.txt")
		out = open("output.txt", "r").read()

		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("out = ")
			print(out)
			print("ans = ")
			print(ans	)
			break
		print("OK", te)

main()