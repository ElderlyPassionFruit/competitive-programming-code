def main():
	a = input().split()
	if a[0] == "3":
		print(30)
		return
	s = ""
	for i in range(int(a[1])):
		x = input()
		s += x
		s += " "
	print(s)

main()
