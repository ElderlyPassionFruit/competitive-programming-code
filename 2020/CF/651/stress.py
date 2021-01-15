import os


def main():
	os.system("make e && make stupidE && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		os.system("./e < in > out")
		out = open("out", "r").read()
		os.system("./stupidE < in > out")
		ans = open("out", "r").read()
		if (out != ans):
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
main()