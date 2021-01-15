import os

def gen(i, j):
	f = open("input.txt", "w")
	print(i, j, file = f)

def main():
	os.system("make best_finder")
	for i in range(3, 6):
		for j in range(1, 6):
			gen(i, j)
			os.system("./best_finder < input.txt > Ans/" + str(i) + "-" + str(j))

main()