import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 9)
	print(n, file = f)
	for i in range(n):
		print(get(0, n), end = " ", file = f)
	print(file = f)
	for i in range(n):
		print(get(1, 10**6), end = " ", file = f)
	print(file = f)

def main():
	os.system("make stupid && make c")
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