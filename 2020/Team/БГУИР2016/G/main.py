n = int(input())
cur_p = 1
cur_num = 0;
cur_p2 = 2
for i in range(n):
	if ((cur_num + cur_p) % cur_p2 == 0):
		cur_num += cur_p
	else:
		cur_num += cur_p * 2
	cur_p2 *= 2;
	cur_p *= 10;
print(cur_num)