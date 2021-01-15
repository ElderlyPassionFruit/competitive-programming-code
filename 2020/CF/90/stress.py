import os
from random import randint as get

def gen():
	f = open("in", "w")
	t = 150 * 10
	print(t, file = f)
	for n in range(1, 151):
		for k in range(0, 10):
			print(n, k, file = f)

def main():
	os.system("make e && make bad")
	for te in range(10**6):
		gen()
		os.system("./e < in > out")
		ans = open("out", "r").read()
		os.system("./bad < in > out")
		out = open("out", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans = ")
			print(ans)
			print("out = ")
			print(out)
			break
		print("OK", te)
main()