import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	t = 1
	print(t, file = f)
	n = get(1, 7)
	print(n, file = f)
	for i in range(n):
		print(get(-1, n - 1), end = " ", file = f)
	print(file = f)

def main():
	os.system("make stupid_solve && make j")
	for te in range(10**6):
		gen()

		os.system("./stupid_solve < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		os.system("./j < input.txt > output.txt")
		out = open("output.txt", "r").read()

		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans =")
			print(ans)
			print("out =")
			print(out)
			break
		print("OK", te)

main()