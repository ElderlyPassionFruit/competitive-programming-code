import os
from random import randint as get

def gen_num():
	n = ""
	for i in range(get(1, 5)):
		if get(1, 2) == 2:
			n += "["
			n += str(get(1, 100))
			n += "]"
			n += str(get(0, 9))
		else:
			n += str(get(0, 9))
	return n

def gen():
	f = open("input.txt", "w")
	print(gen_num(), file = f)
	print(gen_num(), file = f)
	t = get(1, 1000)
	print(t, file = f)
	for i in range(t):
		print(get(1, 100000), end = " ", file = f)
	print(file = f)

def main():
	os.system("make f")
	for te in range(10**6):
		gen()
		os.system("python3 stupid_solve.py < input.txt > output.txt")
		ans = open("input.txt", "r").read()
		os.system("./f < input.txt > output.txt")
		out = open("input.txt", "r").read()

		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt","r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)

main()