import os
from random import randint

def get(l, r):
	return randint(1, 10**10) % (r - l) + l

def get_v(n):
	a1 = get(1, n)
	a2 = get(1, n)
	while a1 == a2:
		a2 += 1
		if a2 == n + 1:
			a2 = 1;
	return a1, a2

def gen():
	f = open("input.txt", "w")
	n = get(2, 10)
	m = get(1, 10)
	#print(n, m)
	print(n, m, file = f)
	for i in range(m):
		a1, a2 = get_v(n)
		b1, b2 = get_v(n)
		print(a1, a2, b1, b2, get(-10, 10), file = f)

def main():
	os.system("clear && make e && make stupid_solve")
	for te in range(10**6):
		gen()
		os.system("./stupid_solve < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		os.system("./e < input.txt > output.txt")
		out = open("output.txt", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans =")
			print(ans)
			print("out =")
			print(out)
			break
		print("OK", te)


main()