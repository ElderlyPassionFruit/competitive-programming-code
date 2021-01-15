import os 
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l

#lett = ["a", "b"]

def gen():
	f = open("input.txt", "w")
	n = get(3, 100)
	print(n, file = f)
	for i in range(n):
		print(get(1, 50), end = " ", file = f);
	print(end = "\n", file = f)
	for i in range(n - 1):
		print(get(1, i + 1), i + 2, file = f)
	q = get(1, 100)
	print(q, file = f)
	for i in range(q):
		t = get(1, 2)
		if t == 1:
			print(t, get(1, n), get(1, 50), file = f)
		else :
			print(t, get(1, n), get(1, n), file = f)
	#s = ""
	#for i in range(n):
	#	s += lett[get(0, len(lett) - 1)]
	#print(s, file = f)


def main():
	for te in range(10 ** 6):
		gen()
		os.system("./a < input.txt > output.txt")
		corr = open("output.txt", "r").read()

		os.system("./b < input.txt > output.txt")
		incr = open("output.txt", "r").read()

		if (corr != incr):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("corr = ")
			print(corr)
			print("incr = ")
			print(incr)
			break
		print("OK", te)

main()