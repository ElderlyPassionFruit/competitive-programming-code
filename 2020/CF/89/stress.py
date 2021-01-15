import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	m = get(1, n)
	print(n, m, file = f)
	for i in range(n):
		print(get(1, 10), end = " ", file = f)
	print(file = f)
	last = 1
	for i in range(m):
		if (last >= 10):
			last += 1
		else:
			last = get(last + 1, 10)
		print(last, end = " ", file = f)
	print(file = f)


def main():
	os.system("make kek && make stupidE")
	for te in range(10**6):
		gen()
		os.system("./kek < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupidE < input.txt > output.txt")
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