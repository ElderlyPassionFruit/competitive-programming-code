import os
from random import randint

def get(l, r):
	return randint(l, r)

def gen():
	f = open("input.txt", "w")
	t = 1;
	n = get(2, 100)
	print(t, file = f)
	print(n, file = f)
	for i in range(n):
		l = get(1, 1000)
		r = get(l, 1000)
		print(l, r, file = f)

def main():
	os.system("clear && make e && make stupid")
	for te in range(10**6):
		gen()
		os.system("./e < input.txt > output.txt")
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