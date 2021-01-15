import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 5)
	print(n, file = f)
	for i in range(2, n + 1):
		print(i, get(1, i - 1), file = f)

def main():
	os.system("make c")
	for te in range(10**6):
		gen()
		a = os.system("./c < input.txt > output.txt")
		if a != 0:
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		print("OK", te)

main()