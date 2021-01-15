def get1(n):
	s = "0" * n
	s += "5"
	s += "0" * (n - 1)
	return s

def get2(n):
	s = "0" * n
	s += "5"
	s += "0" * (n - 2)
	s += "1"
	return s

def get3(n):
	s = "9" * n
	s += "4"
	s += "9" * (n - 1)
	return s

def get4(n):
	s = "9" * n
	s += "4"
	s += "9" * (n - 2)
	s += "8"
	return s

def get(n):
	if n == 1:
		return ["05", "06", "16", "17", "27", "28", "38","39", "49", "50", "60" ,"61", "71", "72", "82", "83", "93", "94"]
	return [get1(n), get2(n), get3(n), get4(n)]

n = int(input())
s = get(n)
s.sort()
print(len(s))
for i in s:
	print(i)
