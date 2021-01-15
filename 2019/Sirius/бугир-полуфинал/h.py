# 1 2 3 5 8
from functools import lru_cache

@lru_cache()
def dp(n, i):
    if i == 0:
        return 0
    ans = 0
    if i == 1:
        for el in [0, 4, 6, 7, 9]:
            if el <= n:
                ans += 1

        return ans
    for el in [0, 4, 6, 7, 9]:
        if i == len(str(n)):
            if el < int(str(n)[0]):
                ans += 5 ** (i - 1)
            elif el == int(str(n)[0]):
                ans += dp(int(str(n)[1:]), i - 1)
        else:
            ans += 5 ** (i - 1)
    return ans


t = int(input())
for i in range(t):
    n = int(input())
    print(dp(n, len(str(n))))