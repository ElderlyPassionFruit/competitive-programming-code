import os

def main():
	os.system("make h && make stupidH && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		os.system("./h < in > out")
		out = open("out", "r").read()
		os.system("./stupidH < in > out")
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