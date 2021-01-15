import os
from random import randint as get

c = ["a","b","c","d"]

def get_s(l):
	s = ""
	for i in range(l):
		s += c[get(0, len(c) - 1)]
	return s

def gen():
	f = open("input.txt", "w")
	n = get(1, 500)
	m = get(1, 500)
	q = get(1, 500) 
	print(n, m, q, file = f)
	print(get_s(n), file = f)
	print(get_s(m), file = f)
	for i in range(q):
		ls = get(1, n)
		rs = get(ls, n)
		lt = get(1, m)
		rt = get(lt, m)
		print(ls, rs, lt, rt, file = f)


def main():
	os.system("make d && make dany")
	for te in range(10**6):
		gen()
		os.system("./d < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		x = os.system("./dany < input.txt > output.txt")
		out = open("output.txt", "r").read()
		if ans != out or x != 0:
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