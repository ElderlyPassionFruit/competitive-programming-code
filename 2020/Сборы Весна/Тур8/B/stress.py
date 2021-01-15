import os 


def main():
	os.system("make b && make youra && make gen")
	for te in range(10**6):
		os.system("./gen > input.txt")
		os.system("./b < input.txt > output.txt")
		my = open("output.txt", "r").readline()
		os.system("./youra < input.txt > output.txt")
		youra = open("output.txt", "r").readline()
		if (my != youra):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("my = ")
			print(my)

			print("youra = ")
			print(youra)
			break
		print("OK", te)

main()
		