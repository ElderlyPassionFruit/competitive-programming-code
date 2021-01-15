import os

def main():
	os.system("make b && make stupidB && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		os.system("./b < in > out")
		out = open("out", "r").read()
		os.system("./stupidB < in > out")
		ans = open("out", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)

main()