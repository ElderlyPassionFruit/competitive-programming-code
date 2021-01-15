def readInt():
	a = input()
	n = ""
	now = ""
	flag1 = False
	flag2 = False
	for i in a:
	#	print(i, n, now, flag1, flag2)
		if i == '[':
			now = ""
			flag1 = True
		elif i == ']':
			flag1 = False
			flag2 = True
		elif flag1:
			now += i		
		elif flag2:
			n += i * int(now)
			flag2 = False
		else:
			n += i
	return int(n)

def main():
	a = readInt()
	#print(a)
	#return
	b = readInt()
	#print(a, b)
	c = str(a + b)
	c = c[::-1]
	#print(a)
	#print(b)
	#print(c)
	t = int(input())
	q = input().split()
	for i in range(t):
		q[i] = int(q[i])
		if (q[i] < len(c)):
			print(c[q[i]], end = " ")
		else:
			print(0, end = " ")
	print()
main()