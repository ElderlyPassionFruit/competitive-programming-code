def sqrt(a):
	l = 0
	r = 10**100
	while (l < r - 1):
		mid = (l + r) // 2
		if (mid * mid <= a):
			l = mid
		else:
			r = mid
	ans = l
	while (ans + 1) * (ans + 1) <= a:
		ans += 1
	return ans

def solve(A, B, C):
	d = B * B - 4 * A * C
	if (d < 0):
		return []
	d = sqrt(d)
	if d * d != B * B - 4 * A * C:
		return []
	if d == 0:
		if (B % (2 * A) != 0):
			return []
		if (B >= 0):
			return []
		return -B // (2 * A)
	else:
		ans = []
		if (-B + d > 0):
			if ((-B + d) % (2 * A) == 0):
				ans.append((-B + d) // (2 * A))
		if (-B - d > 0):
			if ((-B - d) % (2 * A) == 0):
				ans.append((-B - d) // (2 * A)) 
		return ans


n = int(input())

ans = []	

for it in range(100):
	fans = solve(1, 2 ** (it + 1) - 3, -2 * n)
	#print(it, fans)
	for i in fans:
		if (i % 2 == 0):
			continue
		#print("add", i * (2**it))
		ans.append(i * (2 ** it))

ans.sort()
if len(ans) == 0:
	print(-1)
else:
	last = -1
	for i in ans:
		if (i != last):
			print(i)
			last = i