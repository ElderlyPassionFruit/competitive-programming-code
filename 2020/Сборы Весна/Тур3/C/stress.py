import os

def main():
	os.system("make c && make check && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")
		a = os.system("./c < input.txt > output.txt")
		if (a != 0):
			print("RE", te)
			print(open("input.txt", "r").read())
			break
		ans = open("output.txt", "r").readline()
		if (ans == "Fail\n"):
			print("OK", te)
			continue

		f = open("kek.txt", "w")
		x = open("input.txt", "r")
		have = x.readline().split()
		have = x.readline().split()

		#print(have)
		print(1, have[1], have[2], ans, file = f)
		f.close()
		
		os.system("./check < kek.txt > fcheck.txt")
		kek = open("fcheck.txt", "r").read()

		if (kek != "1\n"):
			print(kek)
			print("PE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("out = ")
			print(ans)
			break

		print("OK", te)

main()