import os


def main():
	os.system("make c && make gen && make stupidC")
	for te in range(10**6):
		os.system("./gen > in")
		os.system("./c < in > out")
		out = open("out", "r").read()
		os.system("./stupidC < in > out")
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