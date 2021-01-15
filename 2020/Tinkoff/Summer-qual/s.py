def check(fans, s):
	x = ""
	x += fans
	while len(x) < 10000:
		x += fans
	for i in range(len(x) - len(s)):
		if (x[i:i + len(s)] == s):
			return True
	return False

def get_cycle(s):
	n = len(s)
	#print("s =", s)
	for l in range(n):
		flag = True
		for i in range(l + 1, n, l + 1):
			x = l + 1
			while (i + x > n):
				x -= 1
			flag &= s[:x] == s[i:i + x]
			#print(s[:l + 1], s[i:i + l + 1])
		if (flag):
			return s[:l + 1]

def get1(s, t):
	for i in range(len(s)):
		x = s[:i + 1]
		if (check(x, s) and check(x, t)):
			return get_cycle(x)
	return get_cycle(s + t)

def get2(s, t):
	n = len(s)
	if (len(t) < n):
		n = len(t)
	x = -1
	for i in range(n):
		#print(s[-i - 1:], t[:i + 1])
		if (s[-i - 1:] == t[:i + 1]):
			x = i
	return get_cycle(s + t[x + 1:]) 

s = input()
t = input()

ans = s + t

#if (len(get1(s, t)) < len(ans)):
#	ans = get1(s, t)

#if (len(get1(t, s)) < len(ans)):
#	ans = get1(t, s)

if (len(get2(s, t)) < len(ans)):
	ans = get2(s, t)

if (len(get2(t, s)) < len(ans)):
	ans = get2(t, s)

print(len(ans))