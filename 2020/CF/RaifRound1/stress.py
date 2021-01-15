import os
from random import randint as get

N = 10

def gen():
    f = open("in", "w")
    n = get(1, N)
    print(n, file = f)
    for i in range(n):
        print(get(0, 1), end = "", file = f)
    print(file = f)

def main():
    os.system("make f && make badF")
    for te in range(10**6):
        gen()
        os.system("./f < in > out")
        ans = open("out", "r").read()
        os.system("./badF < in > out")
        out = open("out", "r").read()
        if ans != out:
            print("WA", te)
            print("in = ")
            print(open("in", "r").read())
            print("ans = ")
            print(ans)
            print("out = ")
            print(out)
            return
        print("OK", te)

main()