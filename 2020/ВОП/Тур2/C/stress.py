import os

CNT = 11

def get(x):
	if (x < 10):
		return "0" + str(x)
	else:
		return str(x)

def main():
	os.system("make c")
	for i in range(1, CNT + 1):
		name = get(i)
		os.system("./c < test/" + name + " > ans/" + name + ".a")
main()