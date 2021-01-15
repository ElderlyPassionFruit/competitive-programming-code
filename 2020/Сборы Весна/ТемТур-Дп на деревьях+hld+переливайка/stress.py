import os

def main():
	os.system("make e && make stupid_e && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")

		os.system("./stupid_e < input.txt > output.txt")
		ans = open("output.txt", "r").readline()
		
		os.system("./e < input.txt > output.txt")
		out = open("output.txt", "r").read()
		
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