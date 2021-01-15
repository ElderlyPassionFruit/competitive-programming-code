import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 30)
	print(n, file = f)
	for i in range(2, n + 1):
		print(i, get(1, i - 1), file = f)
	for i in range(n):
		print(get(1, 1000), end = " ", file = f)
	print(file = f)

def main():
	os.system("make g && make stupid_g")
	for te in range(10**6):
		gen()
		os.system("./g < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_g < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (out != ans):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans =", ans)
			print("out =", out)
			break
		print("Ok", te)

main()