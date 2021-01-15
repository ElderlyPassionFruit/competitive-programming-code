n = input()
a = input()

ans = 0
while len(a) > 0:
	x = a[0]
	for i in range(1, len(a)):
		if a[i] != x[-1]:
			x += a[i]
	flag = False
	for i in range(1, len(x) - 1):
		if x[i - 1] == x[i + 1]:
			flag = True
			a = x[:i] + x[i + 1:]
		#	print(1, a)
			break
	ans += 1
	if flag:
		continue

	help = [0] * 26
	for i in x:
		help[ord(i) - ord('a')] += 1
	for i in range(len(x)):
		if help[ord(x[i]) - ord('a')] == 1:
			a = x[: i] + x[i + 1 :]
		#	print(2, a)
			flag = True
			break
	if flag:
		continue

	l = 0 
	r = 10000000000000000000
	for i in range(len(x)):
		for j in range(i + 1, len(x)):
			if x[i] == x[j]:
				if r - l > j - i:
					l = i
					r = j
					break
	a = x[: l + 1] + x[l + 2:]
	#print(3, a)
print(ans)