import os

good = "e"
bad = "h"
gen = "gen_h"

def main():
	os.system("make " + good + " && make " + bad + " && make " + gen)
	for te in range(10**6):
		os.system("./" + gen + " > input.txt")

		#a = os.system("./" + good + " < input.txt > output.txt")
		#ans = open("output.txt", "r").read()

		b = os.system("./" + bad + " < input.txt > output.txt")
		out = open("output.txt", "r").read()

		if (b != 0):
			print("RE", te)
			print("input = ")
			print(open("input.txt", "r").read())
			break
		print("OK", te)

main()