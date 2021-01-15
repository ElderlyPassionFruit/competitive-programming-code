import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 4)
	print(2, n, file = f)
	for i in range(n):
		print("A", get(1, 5), "B", get(1, 5), file = f)

def main():
	os.system("make bad && make stupid")
	for te in range(10**6):
		gen()
		os.system("./bad < input.txt > output.txt")
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