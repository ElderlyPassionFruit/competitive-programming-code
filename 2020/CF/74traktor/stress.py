import os
from random import randint as get

def gen():
	f = open("in", "w")
	print(1, file = f)
	n = get(1, 10)
	print(n, file = f)
	for i in range(n):
		print(get(1, n), end = " ", file = f)
	print(file = f)

def main():
	os.system("make c && make stupidC && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		os.system("./c < in > out")
		out = open("out", "r").read()
		os.system("./stupidC < in > out")
		ans = open("out", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans =")
			print(ans)
			print("out =")
			print(out)
			break
		print("OK", te)
main()