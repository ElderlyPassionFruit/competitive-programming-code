import os
from random import randint as get

MX = 10

def gen():
	f = open("input.txt", "w")
	n = get(1, MX)
	a = get(1, MX)
	print(n, a, file = f)
	for i in range(n):
		print(get(1, MX), end = " ", file = f)
	print(file = f)

def main():
	os.system("make f")
	for te in range(10**6):
		gen()
		a = os.system("./f < input.txt > output.txt")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		print("OK", te)

main()
