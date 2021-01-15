import os

stupid = "stupid_d"
smart = "d"
gen = "gen"

def main():
	os.system("clear && make " + stupid + " && make " + smart + " && make " + gen)
	for te in range(10**6):
		os.system("./" + gen + " > input.txt")

		os.system("./" + stupid + " < input.txt > output.txt")
		ans = open("output.txt", "r").readline()

		os.system("./" + smart + " < input.txt > output.txt")
		out = open("output.txt", "r").readline()

		if ans != out:
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ", ans)
			print("out = ", out)
			break
		print("OK", te)

main()