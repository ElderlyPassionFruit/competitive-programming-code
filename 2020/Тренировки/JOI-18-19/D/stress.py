import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 2)
	print(n, file = f)
	for i in range(2 * n):
		print(get(0, 4), get(0, 4), file = f);

def main():
	os.system("make d && make stupid_solve")
	for te in range(10**6):
		gen()

		os.system("./d < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_solve < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans =", ans)
			print("out =", out)
			break
		print("OK", te)

main()