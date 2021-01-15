import math

def check(a1, a2, a3, A, B):
	if not (-2 * A - B == a1):
		return False
	if not (2 * A * B + A * A == a2):
		return False
	if not (-A * A * B == a3):
		return False
	return True

def main():
	x = input().split()
	a0 = int(x[0])

	a1 = int(x[1]) / a0
	a2 = int(x[2]) / a0
	a3 = int(x[3]) / a0

	#print(a1, a2, a3)
	D = a1 * a1 - 3 * a2
	if D < 0:
		print("No")
		return
	#print(D)

	D = math.sqrt(D)
	A = -a1 + D
	A /= 3
	B = -a1 - 2 * A
	
	#print(A, B)
	if check(a1, a2, a3, A, B):
		print("Yes")
		return

	A = -a1 - D
	A /= 3
	B = -a1 - 2 * A
	
	#print(A, B)
	if check(a1, a2, a3, A, B):
		print("Yes")
		return

	print("No")


main()