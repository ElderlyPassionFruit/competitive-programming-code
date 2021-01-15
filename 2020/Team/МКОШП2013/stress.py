import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")

def main():
	name_good = ""
	name_bad = ""
	os.system("make " + name_good)
	os.system("make " + name_bad)
	for te in range(10**6):
		gen()

		os.system("./" + name_good + " < input.txt > output.txt")
		corr = open("output.txt", "r").read()
		os.system("./" + name_bad + " < input.txt > output.txt")
		incorr = open("output.txt", "r").read()

		if corr != incorr:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("answer = ")
			print(corr)
			print("output = ")
			print(incorr)
			break

		print("OK", te)

main()