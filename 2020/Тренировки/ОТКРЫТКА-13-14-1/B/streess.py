import os

def main():
	os.system("make b && make stupid_b && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")
		os.system("./b < input.txt > output.txt")
		out = open("output.txt", "r").readline()
		os.system("./stupid_b < input.txt > output.txt")
		ans = open("output.txt", "r").readline()
			
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