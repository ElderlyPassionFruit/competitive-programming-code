import os

def main():
	os.system("make 5 && make d && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")
		
		os.system("./5 < input.txt > output.txt")
		ans = open("output.txt", "r").read()

		os.system("./d < input.txt > output.txt")
		out = open("output.txt", "r").read()

		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)

main()
