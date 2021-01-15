import os

def Print(x):
	f = open("in", "w")
	print(x, file = f)

def main():
	os.system("make i && make gen")
	for te in range(10**6):
		#os.system("./gen > in")
		Print(te + 1)
		os.system("python3 i.py < in > out")
		out = open("out", "r").read()
		os.system("./i < in > out")
		ans = open("out", "r").read()
		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
		print(ans)
main()