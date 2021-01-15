f = open("input.txt", "r").readline().split()
n = int(f[0])
m = int(f[1])
k = int(f[2])
p = int(f[3])
q = int(f[4])

print(n, m, k, p, q)

l = -1
r = 10**18 + 228

def check(am):
	global n, m, k, p, q
	return k * am * p >= q * n * m;

while l < r - 1:
	mid = (l + r) // 2
	if (check(mid) == True):
		r = mid
	else:
		l = mid

print(r, file = open("output.txt", "w"))