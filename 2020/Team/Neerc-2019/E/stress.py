import os

os.system("make e")

def gen(n):
    f = open("in", "w")
    print(n, file = f)

for n in range(2, 63):
    gen(n)
    a = os.system("./e < in > out")
    if a != 0:
        print("RE", n)
        break
    print("OK", n)