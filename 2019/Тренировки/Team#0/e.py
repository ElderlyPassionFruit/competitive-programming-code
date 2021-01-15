def main():
	global n, m
	f = open("output.txt", "w")
	if (m == 0):
		print(0, file = f)
		return
	if (n == 0):
		print("IMPOSSIBLE", file = f)
		return
	ans = []

	x = n
	while x < m:
		ans.append(str(x))
		x *= 2

	ans.append(str(0))

	print(len(ans), file = f)
	print(" ".join(ans), file = f)

a = open("input.txt", "r").readline().split()

n = int(a[0])
m = int(a[1])

main()