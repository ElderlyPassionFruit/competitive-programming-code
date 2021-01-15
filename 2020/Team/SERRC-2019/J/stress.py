import os
from random import randint as get

def gen():
    f = open("input.txt", "w")
    n = get(1, 10)
    print(n, file = f)
    for i in range(n):
        print(get(1, n), end = " ", file = f)
    print(file = f)

def main():
    os.system("make j && make stupidJ")
    for te in range(10**6):
        gen()
        os.system("./j < input.txt > output.txt")
        out = open("output.txt", "r").read()
        os.system("./stupidJ < input.txt > output.txt")
        ans = open("output.txt", "r").read()
        if (ans != out):
            print("WA", te)
            print("input = ")
            print(open("input.txt", "r").read())
            print("ans = ", ans)
            print("out = ", out)
            break
        print("OK", te)
main()
