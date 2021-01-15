import os
from random import randint 

def get(l, r):
	return randint(1, 10**10) % (r - l) + l

def help_get(x):
	if x == 0:
		return "0"
	else:
		return "1"
 
def make(x):
	ans = ""
	while x:
		ans += help_get(x % 2)
		x //= 2
	ans = ans[::-1]
	return ans

def gen():
	f = open("input.txt", "w")
	n = get(1, 10)
	print(n, file = f)
	for i in range(n):
		print(make(get(1, 100)), file = f)
	print(make(get(1, 100)), file = f)

good = "stupid_solve"
bad = "g"
check = "g"

def main():
	os.system("make " + good + " && make " + bad + " && make " + check)
	for te in range(10**6):
		gen()
		os.system("./" + good + " < input.txt > output.txt")
		ans = open("output.txt", "r").read()
		os.system("./" + bad  + " < input.txt > output.txt")
		out = open("output.txt", "r").read()
		cnt = 0
		cnt += ans == "-1"
		cnt += out == "-1"
		if cnt % 2 != 0:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)

main()



