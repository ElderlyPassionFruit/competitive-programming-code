import os
from random import randint

def get(l, r):
	return randint(1, 100000000) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	k = get(1, 5)
	n = get(2 * k - 1, 10)
	print(n, k, file = f)
	s = [] 
	for i in range(k):
		x = get(1, n)
		while True:
			flag = True
			for  j in s:
				if j == x:
					flag = False
			if flag:
				break
			x = get(1, n)
		s.append(x)
	s.sort()
	for i in s:
		print(i, file = f)

def main():
	os.system("make b && make stupid_b")
	for te in range(10**6):
		gen()
		os.system("./b < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_b < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (out != ans):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("output = ", out)
			break
		print("OK", te)

main()