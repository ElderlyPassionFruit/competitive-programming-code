import os
from random import randint as get

c = ["a", "b", "c"]

def get_string(n):
	s = ""
	for i in range(n):
		s += c[get(0, len(c) - 1)]
	return s

def gen():
	f = open("input.txt", "w")
	n = get(1, 1000)
	q = get(1, 1000)
	print(n, q, file = f)
	print(get_string(n), file = f)
	for i in range(q):
		t = get(0, 1)
		if t == 0:
			l = get(1, n)
			r = get(l, n)
			print("ask", l, r, file = f)
		else:
			l = get(1, n)
			r = get(l, n)
			x = c[get(0, len(c) - 1)]
			print("set", l, r, x, file = f)

def main():
	os.system("make f && make stupid_f")
	for te in range(10**6):
		gen()
		os.system("./f < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid_f < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if ans != out:
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





