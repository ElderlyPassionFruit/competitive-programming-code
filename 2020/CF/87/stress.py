import os

def main():
	os.system("make e1 && make e2 && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")
		os.system("./e1 < input.txt > output.txt")
		e1 = open("output.txt", "r").read()
		os.system("./e2 < input.txt > output.txt")
		e2 = open("output.txt", "r").read()

		if (e1 != e2):
			print("WA", te, "posos)))")
			print("input = ")
			print(open("input.txt", "r").read())
			print("e1 = ")
			print(e1)
			print("e2 = ")
			print(e2)
			break
		print(te, "youra genius")

main()