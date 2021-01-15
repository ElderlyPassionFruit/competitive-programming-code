import os
from random import randint as rnd

def get(l, r):
	return rnd(l, r)

def gen():
	f = open("input.txt", "w")
	n = get(1, 1000)
	print(n, file = f)
	for i in range(n):
		print(get(1, 1000), end = " ", file = f)
	print(file = f)

def main():
	os.system("make c && make stupid_c")
	for te in range(10**6):
		gen()
		os.system("./c < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_c < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		#print(ans)
		if (out != ans):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
		#print(a)
		#ans = open("input.txt", "r").read()

main()