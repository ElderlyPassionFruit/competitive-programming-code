import os
from random import randint as get

MX = 10

def gen():
    f = open("in", "w")
    T = get(1, MX)
    n = get(1, MX)
    val = [-1] * n
    m = get(1, MX)
    for i in range(m):
        val[get(0, n - 1)] = get(0, MX)
    m = 0
    for i in range(n):
        if val[i] != -1:
            m += 1
    print(T, n, m, file = f)
    for i in range(n):
        if val[i] != -1:
            print(i + 1, val[i], file = f)

def main():
    os.system("make h && make stupid")
    for te in range(10**6):
        gen()
        os.system("./h < in > out")
        out = open("out", "r").read()
        os.system("./stupid < in > out")
        ans = open("out", "r").read()
        if (out != ans):
            print("WA", te)
            print("in = ")
            print(open("in", "r").read())
            print("ans = ")
            print(ans)
            print("out = ")
            print(out)
            break
        print("OK", te)
main()