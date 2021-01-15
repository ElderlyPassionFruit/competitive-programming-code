import os
from random import randint as get

MAXN = 20
MAXA = 100

def gen():
	f = open("input.txt", "w")
	n = get(1, MAXN)
	m = get(1, MAXA)
	print(n, m, file = f)
	for i in range(n):
		print(get(1, MAXA), get(1, MAXA), file = f)

def main():
	os.system("make e && make stupid")
	for te in range(10**6):
		gen()
		os.system("./e < input.txt > output.txt")
		out = float(open("output.txt", "r").read().split()[0])

		os.system("./stupid < input.txt > output.txt")
		ans = float(open("output.txt", "r").read().split()[0])

		d = out - ans
		if (d < 0):
			d = -d
		if (d > 10**(-4)):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)



main()