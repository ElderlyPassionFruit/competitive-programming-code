import os

def main():
	os.system("make bad && make stupid && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")

		a = os.system("./bad < input.txt > output.txt")
		out = open("output.txt", "r").read()
		b = os.system("./stupid < input.txt > output.txt")
		ans = open("output.txt", "r").read()
			
		if (a != 0):
			print("MY RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break

		if (b != 0):
			print("check RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
			
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