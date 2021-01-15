import os
from random import randint as get

c = ['a','b']

def gen():
	f = open("input.txt", "w")
	s = ""
	l = get(3, 10)
	for i in range(l):
		s += c[get(0, len(c) - 1)]
	print(s, file = f)
	q = get(2, 1000)
	print(q, file = f)
	for i in range(q):
		L = get(1, l)
		R = get(L, l)
		print(L, R, file = f)

def main():
	os.system("make b && make stupid_b")
	for te in range(10 ** 6):
		gen()
		os.system("./stupid_b < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		os.system("./b < input.txt > output.txt")
		out = open("output.txt", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
main()