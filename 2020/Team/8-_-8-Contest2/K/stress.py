import os

def abs(a):
	if (a > 0):
		return a
	else:
		return -a

def check(a, b):
	return abs(abs(a) - abs(b)) < 10**(-6)

def main():
	os.system("make k && make stupidK && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		os.system("./k < in > out")
		out = float(open("out", "r").read())
		os.system("./stupidK < in > out")
		ans = float(open("out", "r").read())
		if (check(ans, out) == False):
			print("WA", te)
			print("input = ")
			print(open("in", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
main()