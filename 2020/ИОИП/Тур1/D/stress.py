import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 100)
	k = get(1, n)
	print(n, k, file = f)
	for i in range(n - 1):
		print(get(1, i + 1), end = " ", file = f)
	print(file = f)

def main():
	os.system("make d && make 70")
	for te in range(10**6):
		gen()
		os.system("./70 < input.txt > output.txt")
		ans = open("output.txt").read()
		os.system("./d < input.txt > output.txt")
		out = open("output.txt").read()
		if int(out) != int(ans):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)

main()