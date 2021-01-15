def gcd(a, b):
    if b == 0:
        return a, 1, 0
    g, _x, _y = gcd(b, a % b)
    return g, _y, _x - a // b * _y
 
 
q = int(input())
for _ in range(q):
    t1, t2 = map(int, input().split())
    a, b, c = t1, t2, t1 * t1
 
    g, x, y = gcd(a, b)
    a //= g
    b //= g
    c //= g
 
    x *= c
    y *= c
 
    k = -1 * (x // b)
 
    x += b * k
    y -= a * k
 
    if x == 0:
        x += b
        y -= a
 
    print((max(y, 0) + a - 1) // a)
 