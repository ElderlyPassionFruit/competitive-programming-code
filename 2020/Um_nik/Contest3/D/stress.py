import os
from random import randint as get

def gen():
	f = open("in", "w")
	n = get(1, 4)
	m = get(1, 2) * 2
	print(n, m, file = f)
	for i in range(n):
		print(get(1, 10), get(1, 10), file = f)

def main():
	os.system("make d && make stupidD")
	for te in range(10**6):
		gen()
		os.system("./d < in > out")
		out = open("out", "r").read()
		os.system("./stupidD < in > out")
		ans = open("out", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("out = ", out)
			print("ans = ", ans)
			break
		print("OK", te)
main()