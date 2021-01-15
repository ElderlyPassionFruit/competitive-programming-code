import os

def gen(x, y):
	f = open("in", "w")
	print(x, y, file = f)

def main():
	os.system("make h && make gen")
	for te in range(10**6):
		os.system("./gen > in")
		a = os.system("./h < in > out")
		if (a != 0):
			print("RE", te)
			print("input = ")
			print(open("in", "r").read())
			break
		print("OK", te)
main()