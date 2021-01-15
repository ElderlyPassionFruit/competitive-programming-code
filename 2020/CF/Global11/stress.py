import os

from random import randint as get

N = 999999

def gen(x):
    f = open("in", "w")
    print(get(1, N // 2) * 2 + 1, file = f)

def main():
    os.system("make bruteE && make stupidB && make gen")
    for te in range(1, 10**6, 2):
        #os.system("./gen > in")
        gen(te)
        a = os.system("time ./bruteE < in > out")
        if (a != 0):
            print("RE", te)
            print("input = ")
            print(open("in", "r").read())
            break
        print("OK", te)
        continue
        out = open("out", "r").read()
        os.system("./stupidB < in > out")
        ans = open("out", "r").read()
        #print(ans, out)
        if (ans != out):
            print("WA", te)
            print("input = ")
            print(open("in", "r").read())
            print("out = ")
            print(out)
            print("ans = ")
            print(ans)
            break
        print("OK", te)
main()