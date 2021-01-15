import os

def main():
	os.system("make c && make stupid && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")

		a = os.system("./c < input.txt > output.txt")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		out = open("output.txt", "r").readline();

		os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").readline()
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		if (ans == "DA\n"):
			print("OK", te)

main()