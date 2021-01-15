import os
from random import randint as get

def gen():
	print(get(1,17), file = open("input.txt", "w"))

def main():
	os.system("make f && make stupid")
	for te in range(10**6):
		gen()
		os.system("./f < input.txt > output.txt")
		out = open("output.txt", "r").read()

		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("out = ")
			print(out)
			print("ans = ")
			print(ans)
			break
		print("OK", te)

main()
