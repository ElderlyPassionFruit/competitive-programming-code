import os
from random import randint

def get(l, r):
	return randint(l, r)

c = ["a", "b"]

def get_string(n):
	s = ""
	for i in range(n):
		s += c[get(0, 1)]
	return s

def gen():
	f = open("input.txt", "w")
	n = get(1, 100)
	print(n, file = f)
	print(get_string(n), file = f)
	print(get_string(n), file = f)

def main():
	os.system("make e && make stupid_solve")
	for te in range(10 ** 6):
		gen()
		os.system("./e < input.txt > output.txt")
		out = open("output.txt", "r").readline()
		os.system("./stupid_solve < input.txt > output.txt")
		ans = open("output.txt", "r").readline()
		if (out != ans):
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