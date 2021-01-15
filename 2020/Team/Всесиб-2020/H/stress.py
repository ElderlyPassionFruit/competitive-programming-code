import os
from random import randint as get

N = 100

def gen():
    f = open("input.txt", "w")
    n = get(2, N)
    print(n, file = f)
    for i in range(2, n + 1):
        print(i, get(1, i - 1), get(1, N), get(-N, N), file = f)

def main():
    os.system("make h && make stupid")
    for te in range(10**6):
        gen()
        os.system("./h < input.txt > output.txt")
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
