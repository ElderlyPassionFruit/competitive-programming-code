import os

from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 50)
	m = get(2, n + 1)
	print(n, m, file = f)
	print(0, n, end = " ", file = f)
	used = [0] * (n + 1)
	used[0] = True
	used[n] = True
	for i in range(m - 2):
		x = get(1, n - 1)
		while used[x] == True:
			x = get(1, n - 1)
		used[x] = True
		print(x, end = " ", file = f)
	print(file = f)
	print(get(1, 50), get(1, 50), file = f)

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
			print("ans = ")
			print(ans)
			print("out = ")
			print(out)
			break
		print("OK", te)

main()