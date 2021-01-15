import os 
from random import randint as get

def gen():
	f = open("input.txt", "w")
	n = get(1, 30)
	m = get(1, 30)
	print(n, m, file = f)
	for i in range(m):
		print(get(1, n), end = " ", file = f)
	print(file = f)


def main():
	os.system("make a && make bad")
	for te in range(10**6):
		gen()
		os.system("./a < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		os.system("./bad < input.txt > output.txt")
		out = open("output.txt", "r").read()

		cnt = 0

		if (ans == "-1\n"):
			cnt += 1
		if (out == "-1\n"):
			cnt += 1

		if (cnt == 1):
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