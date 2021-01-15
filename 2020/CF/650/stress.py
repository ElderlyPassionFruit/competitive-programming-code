import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	t = get(1, 1000)
	print(t, file = f)
	for te in range(t):
		n = get(1, 10)
		print(n, file = f)
		for i in range(n):
			print(get(1, 100), end = " ", file = f)
		print(file = f)

def main():
	os.system("make f && make stupidF")
	for te in range(10**6):
		gen()
		os.system("./f < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupidF < input.txt > output.txt")
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
