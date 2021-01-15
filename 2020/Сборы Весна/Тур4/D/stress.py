import os


def main():
	os.system("make d && make stupid && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")
		os.system("./d < input.txt > output.txt")
		out = open("output.txt", "r").readline()
		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").readline()
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