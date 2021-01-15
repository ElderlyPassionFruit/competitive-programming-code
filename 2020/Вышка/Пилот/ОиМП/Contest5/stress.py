import os
from random import randint as get

def gen():
    f = open("in", "w")
    n = get(1, 1000)
    print(n, file = f)
    for i in range(n):
        t = get(1, 3)
        if (t == 1):
            print(1, get(1, 10), get(1, 10), file = f)
        elif (t == 2):
            print(2, get(1, 10), file = f)
        elif (t == 3):
            print(3, get(1, 10), file = f)
def main():
    os.system("make o && make stupidO")
    for te in range(10**6):
        gen()
        os.system("./o < in > out")
        out = open("out", "r").read()
        os.system("./stupidO < in > out")
        ans = open("out", "r").read()
        if (ans != out):
            print("WA", te)
            print(open("in", "r").read())
            print("out = ", out)
            print("ans = ", ans)
            return
        print("OK", te)
main()