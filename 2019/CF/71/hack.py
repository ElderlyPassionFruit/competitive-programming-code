f = open("input.txt", "w")
n = int(5e5)
print(n, file = f)
for i in range(n - 1):
	print("1 500000 1000", file = f)
print("2 701 0", file = f)