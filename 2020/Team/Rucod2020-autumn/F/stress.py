def gen(i):
    f = open("in.txt", "w")
    print(i, file = f)

import os

for i in range(1, 101):
    gen(i)
    os.system("./f < in.txt > out.txt")