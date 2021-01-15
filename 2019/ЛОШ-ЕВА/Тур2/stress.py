import os
from random import randrange

def get(l, r):
	return randrange(1, 10000000) % (r - l + 1) + l

s = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

def gen():
	n = get(10, 20)
	f = open("input.txt", "w")
	print(n, file = f)
	for i in range(2, n + 1):
		u = get(1, i - 1)
		print(i, u, file = f)

	h = ""
	for i in range(n):
		h += s[get(0, 3)]
	print(h, file = f)



for te in range(1000000000):
	gen()
	os.system("./a")
	correct = open("output.txt", "r").readline()

	os.system("./b")
	incorrect = open("output.txt", "r").readline()

	if (correct != incorrect):
		print("WA\t", te)
		print(open("input.txt", "r").read())

		print("correct", correct)
		print("incorrect", incorrect)
		
		break
	else:
		print("OK\t", te)