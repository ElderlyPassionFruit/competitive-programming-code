n = int(input())
a = input()
b = "" + a

ans = 10**100000 + 1

s1 = a[:n//2:]
s2 = a[n//2::]

i = 0;
for j in s2:
	if not j == "0":
		s1 += s2[:i]
		s2 = s2[i:]
		print(s1, s2)
		ans = min(ans, int(s1) + int(s2))
		break
	i += 1

s1 = b[:(n + 1)//2:-1]
s2 = b[(n + 1)//2:]
print(s1, s2)
i = 0;
for j in s1:
	if not j == "0":
		s2 = s1[:i:-1] + s2
		s1 = s1[i::-1]
		print(s1, s2)
		ans = min(ans, int(s1) + int(s2))
		break
	i += 1

print(ans)