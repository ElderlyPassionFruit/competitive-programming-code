import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(3, 6)
	k = get(1, n // 2)
	print(n, k, file = f)
	for i in range(2, n + 1):
		print(get(1, i - 1), i, file = f)

	for i in range(n):
		print(get(1, k), end = " ", file = f)

	print(file = f)

def main():
	os.system("make a && make stupid_solve")
	for te in range(10**6):
		gen()
		os.system("./a < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_solve < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans =", ans)
			print("out =", out)
			break

		print("OK", te)


main()