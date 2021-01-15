import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = 40
	print(n, file = f)
	for i in range(n):
		print(get(1, 100), end = " ", file = f)
	print(file = f)

def main():
	os.system("make j && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")

		a = os.system("./j < input.txt > output.txt")
		out = open("output.txt", "r").read()
		
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		#os.system("./stupid_g < input.txt > output.txt")
		#ans = open("output.txt", "r").read()
		
		#if (ans != out):
		#	print("WA", te)
		#	print("input = ")
		#	print(open("input.txt", "r").read())
		#	print("ans = ", ans)
		#	print("out = ", out)
		#	break
		print("OK", te)

main()