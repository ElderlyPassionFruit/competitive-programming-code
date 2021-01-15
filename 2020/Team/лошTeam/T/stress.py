import os
from random import randint as get 

def main():
	os.system("make t && make stupid && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")
		os.system("./t < input.txt > output.txt")
		out = open("output.txt", "r").read()
		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = "	)
			print(ans)
			print("out = ")
			print(out)
			return
		print("OK", te)

main()