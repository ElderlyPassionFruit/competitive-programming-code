from decimal import *

MAXN = 21

fact = [0 for i in range(MAXN)]

def build():
    fact[0] = 1
    for i in range(1, MAXN):
        fact[i] = fact[i - 1] * i

n, a, b = None, None, None
p = [0 for i in range(MAXN)]
used = p.copy()

def calc_cycles():
    ans = 0
    for i in range(n):
        if used[i]:
            continue
        v = i
        ans += 1
        while not used[v]:
            used[v] = 1
            v = p[v] - 1
    return ans

def cost_cycle(cnt):
    return n - cnt

def get(n, k):
    if n == 0 and k == 0:
        return 1
    if n == 0 or k == 0:
        return 0
    return get(n - 1, k - 1) - (n - 1) * get(n - 1, k)

def fget(n, k):
    return abs(get(n, k))

def get_path(cnt):
    ans = Decimal(fact[n]) / fget(n, cnt)
    return ans

def main():
    global n, a, b, p
    build()
    n, a, b = input().split()
    n = int(n)
    a, b = map(Decimal, [a, b])
    p = list(map(int, input().split()))
    ans = cost_cycle(calc_cycles()) * a
    fans = Decimal(0)
    for i in range(1, n + 1):
        if (i != calc_cycles()):
            fans += get_path(i) * b + cost_cycle(i) * a
    ans = min(ans, fans / n)
    print(ans)

main()
