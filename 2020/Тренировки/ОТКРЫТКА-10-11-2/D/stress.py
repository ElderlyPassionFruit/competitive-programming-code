import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	print(n, file = f)
	a = []
	for i in range(n):
		x = get(1, 5)
		y = get(1, 5)
		while (x, y) in a:
			x = get(1, 5)
			y = get(1, 5)
		a.append((x, y))
		print(x, y, file = f)

def main():
	os.system("make d && make stupid_d")
	for te in range(10**6):
		gen()
		os.system("./stupid_d < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		os.system("./d < input.txt > output.txt")
		out = open("output.txt", "r").read()

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


