import os
from random import randint as get

MAX = 10

def gen():
	f = open("input.txt", "w")
	n = get(1, MAX)
	print(MAX, MAX, n, file = f)
	for i in range(n):
		print(get(1, MAX), get(1, MAX), file = f)
	t = get(1, MAX)
	print(t, file = f)
	for i in range(t):
		print(get(1, MAX), get(1, MAX), get(1, MAX), get(1, MAX), file = f)

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
			print("ans =")
			print(ans)
			print("out =")
			print(out)
			return
		print("OK", te)

main()