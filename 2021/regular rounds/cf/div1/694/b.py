from random import randint as get

def smartCheck(a):
    x = int(a**(1/2))
    x -= 5
    if (x < 0):
        x = 0
    while ((x + 1) * (x + 1) <= a):
        x += 1
    return x * x == a


def gcd(a, b):
    while b:
        a %= b
        a, b = b, a
    return a

def check(a, b):
    g = gcd(a, b)
    return smartCheck((a // g) * (b // g))

def calcAns(a):
    ans = 0
    for i in a:
        cnt = 0
        for j in a:
            if check(i, j):
                cnt += 1
        if cnt > ans:
            ans = cnt
    return ans

def make(a):
    na = []
    for i in a:
        x = []
        for j in a:
            if check(i, j):
                x.append(j)
        fans = 1
        for have in x:
            fans *= have
        na.append(fans)
    return na

def test():
    n = get(1, 3)
    a = []
    for i in range(n):
        a.append(get(1, 10))
    #n = 3
    #a = [1, 2, 2]
    cnt = 0
    last = calcAns(a)
    print("last =", last)
    print(a, calcAns(a))
    for i in range(2):
        a = make(a)
        print(a, calcAns(a))
        if (last != calcAns(a) and i != 0):
            last = calcAns(a)
            cnt += 100
        elif (last != calcAns(a)):
            cnt += 1
            last = calcAns(a)
    if (cnt == 1 and calcAns(a) != n - 1):
        cnt = 100
    print("cnt =", cnt)
    return cnt

for te in range(10**6):
    cnt = test()
    if (cnt > 1):
        print(cnt)
        break