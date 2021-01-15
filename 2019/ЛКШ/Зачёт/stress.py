import os 
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

lett = ["a"]

def gen():
	f = open("input.txt", "w")
	n = get(3, 5)
	for i in range(n):
		print(get(1, 5), end = " ", file = f)
	print(end = "\n", file = f)
	q = get(3, 5)
	for i in range(q):
		print(get(1, 5), file = f)
	

def main():
	for te in range(10**6):
		gen()

		os.system("./a < input.txt > output.txt")
		corr = open("output.txt", "r").read()

		os.system("./b < input.txt > output.txt")
		incr = open("output.txt", "r").read()

		if (corr != incr):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("corr = ")
			print(corr)
			print("incr = ")
			print(incr)
			break
		print("OK", te)

main()