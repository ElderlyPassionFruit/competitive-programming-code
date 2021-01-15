import os
from random import randint as get

MX = 20

def gen():
	f = open("input.txt", "w")
	print(get(1, MX), get(1, MX), get(1, MX), get(1, MX), file = f)

def main():
	os.system("make j")
	for te in range(10**6):
		gen()
		a = os.system("./j < input.txt > output.txt")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		print("OK", te)

main()
