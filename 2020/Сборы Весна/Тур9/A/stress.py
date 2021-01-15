import os
from random import randint as get

c = ['R', 'S']

MAX = 10
def gen():
	f = open("input.txt", "w")
	n = get(1, MAX)
	m = get(1, MAX)
	k = get(1, MAX)
	print(n, m, k, file = f)
	for i in range(k):
		if (get(1, 2) == 1):
			print(c[0], get(1, n), get(0, 10**9), file = f)
		else:
			print(c[1], get(1, m), get(0, 10**9), file = f)

def main():
	os.system("make a && make stupid")
	for te in range(10**6):
		gen()
		os.system("./a < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		if (ans != out):
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