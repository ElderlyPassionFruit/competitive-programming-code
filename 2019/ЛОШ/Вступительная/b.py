a = input().split()

x1 = []
x1.append(int(a[0]))
x1.append(int(a[2]))
x1.sort()

y1 = []
y1.append(int(a[1]))
y1.append(int(a[3]))
y1.sort()

b = input().split()

x2 = []
x2.append(int(b[0]))
x2.append(int(b[2]))
x2.sort()

y2 = []
y2.append(int(b[1]))
y2.append(int(b[3]))
y2.sort()

def check2(a, b, x):
	return a <= x and b >= x

def check(a, b):
	return check2(a[0], a[1], b[0]) or check2(a[0], a[1], b[1]) or check2(b[0], b[1], a[0]) or check2(b[0], b[1], a[1])	


if check(x1, x2) and check(y1, y2):
	print("Yes")
else:
	print("No")