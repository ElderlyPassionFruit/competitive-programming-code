import os


def gen(a, b):
    f = open("in", "w")
    print("1", file = f)
    print(a, b, file = f)

os.system("make a")

for a in range(0, 201):
    for b in range(0, 201):
        gen(a, b)
        x = os.system("./a < in > out")
        if (x != 0):
            print("RE", a, b)
        