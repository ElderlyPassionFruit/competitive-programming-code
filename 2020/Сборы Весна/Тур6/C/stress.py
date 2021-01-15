import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 200)
	m = n - 1
	print(1, file = f)
	print(n, m, file = f)
	for i in range(2, n + 1):
		print(i - 1, i, file = f)



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