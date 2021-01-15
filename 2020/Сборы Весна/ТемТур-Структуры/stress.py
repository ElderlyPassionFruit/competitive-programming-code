import os
from random import randint as get

c = ['+', '-', '?']

MAXVAL = 1

def gen():
	f = open("input.txt", "w")
	n = get(2, 3)
	q = get(1, 4)
	print(n, q, file = f)
	for i in range(2, n + 1):
		print(get(1, i - 1), end = " ", file = f)
	print(file = f)
	for i in range(n):
		print(get(1, MAXVAL), end = " ", file = f)
	print(file = f)
	used = [True] * n
	cnt = n
	for i in range(q):
		t = get(0, 2)
		if t == 0 and cnt == n:
			t = 1;
		if (t == 1 and cnt == 1):
			t = 2
		if t == 0:
			v = get(1, n - 1)
			while used[v]:
				v = get(1, n - 1)
			cnt += 1
			used[v] = True
			v += 1
			print(c[t], v, file = f)
		elif t == 1:
			v = get(1, n - 1)
			while used[v] == False:
				v = get(1, n - 1)
			cnt -= 1
			used[v] = False
			v += 1
			print(c[t], v, file = f)
		else:
			v = get(1, n)
			d = get(1, MAXVAL)
			print(c[t], v, d, file = f)

	
def main():
	os.system("make h && make stupid")
	for te in range(10**6):
		gen()
		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		os.system("./h < input.txt > output.txt")
		out = open("output.txt", "r").read()
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