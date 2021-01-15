import os
from random import randrange

s = []

def get(l, r):
	return randrange(1, 10000000) % (r - l + 1) + l


def gen():
	global s
	s = []
	n = get(5, 5)
	m = get(10, 10)
	s.append(str(n) + " " + str(m))

	f = open("input.txt", "w")
	print(n, m, file = f)
	
	for i in range(m):
		u = get(1, n);
		v = get(1, n);
		if u > v:
			u , v = v, u
		while (u == 1 and v == 2):
			u = get(1, n);
			v = get(1, n);
			if u > v:
				u , v = v, u
			
		l = get(1, 10);
		lum = get(1, 10);
		print(u, v, l, lum, file = f)
		s.append(str(u) + " " + str(v) + " " + str(l) + " " + str(lum))


for te in range(10000000):
	gen()
	#print("OK))")
	os.system("./good")
	check = int(open("output.txt", "r").readline())
	#print(check)
	if check == 0:
		continue
	#print("KEK")

	os.system("./a")
	correct = open("output.txt", "r").readline()
	
	f = open("fin.txt", "w")
	for i in s:
		print(i, file = f)

	print(open("output.txt", "r").read(), file = f)
	
	os.system("./check")
	flag = bool(open("fout.txt", "r").readline())


	if (flag == False):
		print("WA\t", te)
		print(open("input.txt", "r").read())
		print("incorrect")
		print(open("output.txt", "r").read())
		break
	else:
		print("OK\t", te)