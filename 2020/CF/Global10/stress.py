import os

def gen(x, y):
	f = open("in", "w")
	print(x, y, file = f)

def main():
	os.system("make d && make stupidD && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		a = os.system("./d < in > out")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("in", "r").read())
			break
		#print("OK", te)
		#continue
		out = open("out", "r").read()
		os.system("./stupidD < in > out")
		ans = open("out", "r").read()
		#print(ans, out)
		if (ans != out):
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("out = ")
			print(out)
			print("ans = ")
			print(ans)
			break
		print("OK", te)
main()