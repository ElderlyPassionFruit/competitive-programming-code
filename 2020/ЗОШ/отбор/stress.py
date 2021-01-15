import os

smart = "j"
stupid = "stress_j"
gen = "gen_j"

TEST = 2
PATH = "tests_j/"
def get(i):
	if i < 10:
		return "0" + str(i)
	return str(i)

def main():
	os.system("make " + smart + " && make " + stupid + " && make " + gen)
	for i in range(1, TEST + 1):
		print(open(PATH + get(i), "r").read(), file = open("input.txt", "w"))
		os.system("./" + smart + " < input.txt > out1.txt")
		os.system("./" + stupid + " < input.txt > out2.txt")
		ans = open("out2.txt", "r").read()
		output = open("out1.txt", "r").read()
		if (ans != output):
			print("WA mytest", i)
			print("input = ")
			print(open("input.txt", "r").read())
			print("ans = ")
			print(ans)
			print("output = ")
			print(output)
			return
		print("OK mytest", i)
	#return
	for te in range(1000000):
		os.system("./" + gen + " > input.txt")
		os.system("./" + smart + " < input.txt > out1.txt")
		os.system("./" + stupid + " < input.txt > out2.txt")
		ans = open("out2.txt", "r").read()
		output = open("out1.txt", "r").read()
		if (ans != output):
			print("WA", te)
			print("input = ")
			print(open("input.txt", "r").read(), file = open(PATH + get(TEST + 1), "w"))
			print(ans, file = open(PATH + get(TEST + 1) + "a", "w"))
			print(open("input.txt", "r").read())
			print("ans = ")
			print(ans)
			print("output = ")
			print(output)
			return
		print("OK", te)
main()