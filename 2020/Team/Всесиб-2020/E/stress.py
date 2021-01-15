import os
from random import randint as get

N = 2

def gen():
    f = open("input.txt", "w")
    n = get(3, N)
    print(n, file = f)
    for i in range(n):
        print(get(0, 2), end = " ", file = f)
    print(file = f)

def main():
    os.system("make e && make stupid")
    for te in range(10**6):
        gen()
        os.system("./e < input.txt > output.txt")
        out = open("output.txt", "r").read()
        os.system("./stupid < input.txt > output.txt")
        ans = open("output.txt", "r").read()
        if out != ans:
            print("WA", te)
            print("input = ")
            print(open("input.txt", "r").read())
            print("ans = ")
            print(ans)
            print("out = ")
            print(out)
            break
        print("OK", te)

main()
