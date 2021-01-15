import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = 5000
	l = 5000
	print(n, l, file = f)
	for i in range(n):
		print(get(1, 10**9), end = " ", file = f)
	print(file = f)
def main():
	gen()
	return;
	os.system("make && make")
	for te in range(10**6):
		gen()
		os.system("./ < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./ < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans =")
			print(ans)
			print("out =")
			print(out)
			return
		print("OK", te)

main()