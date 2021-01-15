import os
from random import randint as rnd

def get(l, r):
	return rnd(l, r)

c = ['a', 'b']

def gen_string():
	Len = get(1, 1000)
	s = ""
	for i in range(Len):
		s += c[get(0, len(c) - 1)]
	return s

def gen():
	f = open("input.txt", "w")
	s = gen_string()
	n = len(s)
	print(s, file = f)
	q = get(1, 1000)
	print(q, file = f)
	for i in range(q):
		t = get(1, 2)
		l = get(1, n)
		r = get(l, n)
		print(t, l, r, file = f)


def main():
	os.system("make main && make stupid && make gen")
	for te in range(10**6):
		#gen()
		os.system("./gen > input.txt")
		a = os.system("./main < input.txt > output.txt")
		out = open("output.txt", "r").read()
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break

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
		#print(a)
		#ans = open("input.txt", "r").read()

main()