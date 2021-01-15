import os
from random import randint as rnd

def get(l, r):
	return rnd(1, 10**20) % (r - l + 1) + l

def gen():
	f = open("input.txt", "w")
	print(9**18 - 9, 9, file = open("input", "w"))
	return
	n = get(10**17, 10**18)
	d = get(1, 9)
	while n % d:
		d = get(1, 9)
	print(n, d, file = f)

def get_smart():
	print(9**18 - 9, 9, file = open("input", "w"))
		
	return;
	x = 9
	now = 8
	while True:
		add = now * 9
		if x + add > 10**18:
			break
		x += add
		now *= 8
	print(x, 9, file = open("input.txt", "w"))

def main():
	os.system("clear && make b_tikhon")
	fans = 0
	for te in range(10**6):
		get_smart()
		#gen()
		os.system("./b_tikhon < input.txt > output.txt")
		out = open("output.txt", "r").read()
		if fans < len(out):
			fans = len(out)
		print(fans)
		if (len(out) > 1000):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)
main()