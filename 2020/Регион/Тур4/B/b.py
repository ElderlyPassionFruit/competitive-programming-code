def get_substr(s, l, r):
	ans = ""
	for i in range(l, r + 1):
		ans += s[i]
	return ans

def get_border(s, t):
	n = len(s)
	if (len(t) < len(s)):
		n = len(t)
	ans = 0
	for i in range(n):
		if (get_substr(s, len(s) - 1 - i, len(s) - 1) == get_substr(t, 0, i)):
			ans = i + 1
	if (ans == len(s)):
		return -1
	return ans;

c = ["A", "B"]

def build(s):
	ans = []
	x0 = 0
	if (s[0] == "A"):
		x0 = 1
	x1 = x0 ^ 1
	ans.append([x0, x1])
	now = ""
	for i in range(len(s) - 1):
		now += s[i]
		add = []
		for j in range(2):
			add.append(get_border(now + c[j], s))
		ans.append(add)
	return ans

s = input()
n = int(input())

dp = []
for i in range(n + 1):
	x = []
	for j in range(len(s)):
		x.append(0)
	dp.append(x)

dp[0][0] = 1
#print(dp)

nxt = build(s)
print("Nxt =", nxt)
x = (n + 1) // 2
#print("x =", x)
for i in range(x):
	for j in range(0, len(s)):
		for k in range(2):
			if (dp[i][j] == 0 or nxt[j][k] == -1):
				continue
			dp[i + 1][nxt[j][k]] += dp[i][j]

print("dp =", dp)
ans = 0

def check(s, t):
	i = 0
	while i + len(t) - 1 < len(s):
		if (get_substr(s, i, i + len(t) - 1) == t):
			return False
		i += 1
	return True



def Check(Len):
	x = s[:Len + 1]
	y = x[::-1]
	if n % 2 == 1:
		y = y[1:]
	fans = x + y
	print(fans, s)
	return check(fans, s)

for i in range(0, len(s)):
	if (Check(i)):
		ans += dp[x][i]
print(ans)










