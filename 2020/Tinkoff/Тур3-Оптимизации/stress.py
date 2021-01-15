import os 
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	n = get(1, 300)
	k = get(1, n)
	print(n, k, file = f)
	for i in range(n):
		print(get(0, 100), end = " ", file = f)
	print(end = "\n", file = f)

def main():
	os.system("make e")
	os.system("make stupid_e")

	for te in range(10**6):
		gen()
		os.system("./e < input.txt > output.txt")
		corr = open("output.txt", "r").read()
		os.system("./stupid_e < input.txt > output.txt")
		incorr = open("output.txt", "r").read()
		if (corr != incorr):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", incorr)
			print("output = ", corr)
			break
		print("OK", te)

main()