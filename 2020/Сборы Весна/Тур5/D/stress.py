import os
from random import randint as get

c = ['a', 'b', 'c', 'e']

def gen():
	f = open("input.txt", "w")
	n = get(6, 7)
	print(n, file = f)
	for i in range(n - 1):
		print(c[get(0, len(c) - 1)], end = "", file = f)
	print(c[get(0, len(c) - 2)], file = f)

def main():
	os.system("make bad && make stupid")
	for te in range(10**6):
		gen()
		os.system("./bad < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		
		if ans != out:
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