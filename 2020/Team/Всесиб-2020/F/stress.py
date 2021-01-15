import os
from random import randint as get

def gen():
    f = open("input.txt", "w")
    b = get(1, 10)
    m = get(1, 10)
    n = get(1, 10)
    print(b, m, n, file = f)
    for i in range(n):
        print(get(1, 10), file = f)

def main():
    os.system("make f && make stupid")
    for te in range(10**6):
        gen()
        os.system("./f < input.txt > output.txt")
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
