import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**10) % (r - l + 1) + l;

lett = ['a', 'b', 'c', 'd', 'e']

def gen():
	l = get(3, 100)
	s = ""
	for i in range(l):
		s += lett[get(0, 4)]
	f = open("input.txt", "w")
	print(l - 2, file = f)
	x = []
	for i in range(l - 2):
		print(s[i : i + 3], file = f)
		x.append(s[i : i + 3])
	#print(s, x)
	x.sort()
	return s, x


def main():
	for te in range(10**6):
		s, x = gen()

		os.system("./a")
		have = open("output.txt", "r").readline()
		y = []
		l = len(have) - 1
		#print(have) 
		for i in range(l - 2):
			y.append(have[i : i + 3])
		#print(y)
		y.sort()
		if not x == y:
			print("WA", te)
			print(s)
			print(x)
			print(have)
			print(y)
			print(open("input.txt", "r").read())
			break
		print("OK", te)

main()
