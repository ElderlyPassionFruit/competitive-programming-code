import os

def main():
	os.system("make i && make stupidI && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		os.system("./i < in > out")
		out = open("out", "r").read()
		os.system("./stupidI < in > out")
		ans = open("out", "r").read()
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans = ")
			print(ans)
			print("out = ")
			print(out)
			break
		print("OK", te)
main()