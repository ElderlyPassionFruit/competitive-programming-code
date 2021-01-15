import os
from random import randint 

def get(l, r):
	return randint(l, r)

c = ["a", "b"]

def get_string():
	n = get(1, 10)
	#print(n)
	s = ""
	for i in range(n):
		s += c[get(0, 1)]
	return s

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	print(n, file = f)
	for i in range(n):
		print(get_string(), file = f)
	n = get(1, 10)
	print(n, file = f)
	for i in range(n):
		print(get_string(), file = f)
		
def main():
	os.system("make f && make stupid")
	for te in range(10**6):
		gen()
		os.system("./f < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid < input.txt > output.txt")
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