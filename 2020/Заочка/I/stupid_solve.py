def check(x):
	Sum = 0
	s = x
	while s:
		if s % 10 == 0:
			return False
		Sum += s % 10
		s //= 10
		if x % Sum != 0:
			return False
	return True

#n = int(input())

c = ['1', '2']

def get(mask):
	ans = ""
	while mask:
		ans += c[mask % 2]
		mask //= 2
	return int(ans)

def get_len(x):
	ans = 0;
	while x:
		ans += 1
		x //= 10
	return ans

def solve():
	for mask in range(1, 1 << 30):
		x = get(mask)
		if (check(x)):
			print(x, get_len(x))

#solve()

ans = [0] * 100

def main():
	for i in range(10**20):
		x = 12212122112
		x = 8433243122112
		x += i * (10**get_len(x))
		if (check(x)):
			print(x, get_len(x))
	
	print(ans) 
	return
	#for n in range(5, 20):
	#a = []
	x = 7534899112212122112
	for i in range(1, 10**7):
		if (check(i * 10 ** 20 + x)):
			x = str(i * 10 ** 20 + x)
			x = x[::-1]
			a.append(x)

	a.sort()
	print(a[0])

#main()

def clear(a):
	a.sort()
	ans = []
	for i in a:
		if len(ans) == 0 or ans[-1] != i:
			ans.append(i)
	return ans

def next_it(a):
	b = []
	for i in a:
		for j in a:
			if (check(int(i + j))):
				b.append(int(i + j))
				#print(i + j)
	b.sort()
	print(b[-1])

	for i in b:
		a.append(str(i))
	a = clear(a)
	return a
	

def stupid_solve():
	a = []
	for i in range(1, 10**8):
		if (check(i)):
			a.append(str(i))
			#print(i)

	for i in range(10):
		a = next_it(a)
		print("sz =",len(a))
		#print(a[-1])

	#x = 1
	#print(a[0])
	#for i in range(len(a)):
	#	if (a[i][:x] != a[i - 1][:x]):
	#		print()
	#	print(a[i])
#main()
#stupid_solve()

def check_zero(x):
	while x:
		if (x % 10 == 0):
			return False
		x //= 10
	return True

def very_stupid_solve():
	a = 697203752297124771645338089353123035568
	#print(check(163475455412363736581997357824894817518735664))
	for i in range(1, 10**9):
		x = a * i
		#if (check_zero(x)):
		#	print(x)
		#print(x)
		if (check(x)):
			print(x)

very_stupid_solve()