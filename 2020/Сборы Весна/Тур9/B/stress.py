import os
from random import randint as get


MAX = 100
def gen():
	f = open("input.txt", "w")
	n = get(1, MAX)
	print(n, file = f)
	a = []
	for i in range(n):
		a.append(get(0, MAX * 100))
		print(a[-1], end = " ", file = f)
	print(file = f)
	for i in range(n):
		x = get(0, a[i])
		a[i] -= x
		print(x, end = " ", file = f)
	print(file = f)
	for i in range(n):
		x = get(0, a[i])
		a[i] -= x
		print(x, end = " ", file = f)
	print(file = f)
	x = get(0, 10)
	print(x, file = f)	


def main():
	os.system("make b && make stupid")
	for te in range(10**6):
		gen()
		os.system("./b < input.txt > output.txt")
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