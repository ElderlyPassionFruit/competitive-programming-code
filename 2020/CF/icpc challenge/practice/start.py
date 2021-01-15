import os
os.system("make b")
for i in range(1, 5):
	print("i = ", i)
	os.system("./b < b" + str(i) + ".in > b" + str(i) + ".out")