
def check(a, b):
    x = 2 ** 60 - 1
    if (b <= 0):
        a = -a
        b = -b
    if (a <= 0):
        if (a <= -x):
            return True
        a = 0
    return a // x * x + x <= b

m = input().split()
a = int(m[0])
b = int(m[1])
l = 0
r = 10**1000

while l < r - 1:
    mid = (l + r) // 2
    if (check(a * mid, b * mid)):
        r = mid
    else:
        l = mid
print(r)