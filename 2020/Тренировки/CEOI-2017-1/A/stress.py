import os
from random import randint as get

MAX = 19

def gen():
	f = open("input.txt", "w")
	n = get(1, MAX)
	m = get(n - 1, MAX)
	print(n, m, file = f)
	for i in range(m):
		print(get(1, n), get(1, n), file = f)
	q = get(1, 3)
	print(q, file = f)
	for i in range(q):
		print(get(1, n), get(1, n), file = f)

def main():
	os.system("make a && make stupid_solve")
	for te in range(10**6):
		gen()
		os.system("./stupid_solve < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (ans[0] == '-'):
			continue
		os.system("./a < input.txt > output.txt")
		out = open("output.txt", "r").read()

		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
main()