import os 
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	print(n, file = f)
	for i in range(n):
		l = get(1, 10)
		r = get(l, 10)
		print(l, r, file = f)

def main():
	os.system("make c && make stupid_c")
	for te in range(10**6):
		gen()
		os.system("./c < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_c < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (out.split()[0] != ans.split()[0]):
			print("WA",te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK",te)
main()