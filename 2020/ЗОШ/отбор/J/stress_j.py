import os

SMART = "smart_j"
STUPID = "stupid_j"
GEN = "gen_j"

def main():
	os.system("make " + SMART + " && make " + STUPID + " && make " + GEN)
	for te in range(1000000):
		os.system("./" + GEN + " > input.txt")
		os.system("./" + STUPID + " < input.txt > out1.txt")
		os.system("./" + SMART  + " < input.txt > out2.txt")
		ans = open("out1.txt", "r").read()
		output = open("out2.txt", "r").read()
		if (ans != output):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ")
			print(ans)
			print("output = ")
			print(output)
			break
		print("OK", te)

main()