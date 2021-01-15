import os
from random import randint as get

MX = 6
MXVAL = 10**5
def gen():
	f = open("input.txt", "w")
	for i in range(9):
		print(get(0, MX), end = " ", file = f)
	print(file = f)
	q = get(1, 10000)
	print(q, file = f)
	for i in range(q):
		print(get(0, MXVAL), end = " ", file = f)
	print(file = f)

def main():
	os.system("make k && make stupid")
	for te in range(10**6):
		gen()
		a = os.system("./k < input.txt > output.txt")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		out = open("output.txt", "r").read()
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

main()
