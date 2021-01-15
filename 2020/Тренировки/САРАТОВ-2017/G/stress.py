import os
from random import randint as get

MX = 20

def gen():
	f = open("input.txt", "w")
	n = get(1, MX)
	n *= 2
	print(n, file = f)
	for i in range(n):
		print(get(1, MX), end = " ", file = f)
	print(file = f)

def main():
	os.system("make g")
	for te in range(10**6):
		gen()
		a = os.system("./g < input.txt > output.txt")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		print("OK", te)

main()
