import os

CNT_TESTS = 10

def main():
	first = 0
	second = 0
	draw = 0
	for i in range(CNT_TESTS):
		name_test = "tests/"+ str(i) + ".txt"
		command = "./game < " + name_test + " > out.txt"
		os.system(command)
		result = open("out.txt").readline().split()
		if (int(result[0]) > int(result[1])):
			first += 1
		elif (int(result[0]) < int(result[1])):
			second += 1
		else:
			draw += 1
	print("first  =", first)
	print("second =", second)
	print("draw   =", draw)

main()