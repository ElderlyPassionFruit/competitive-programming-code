import os
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	m = n
	print(n, m, file = f)
	for i in range(n):
		print(get(1, 20), get(1, 20), file = f)
	for i in range(m):
		print(get(1, 20), file = f)

def main():
	os.system("make b && make stupid_solve")
	for te in range(10**6):
		gen()

		os.system("./b < input.txt > output.txt")
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