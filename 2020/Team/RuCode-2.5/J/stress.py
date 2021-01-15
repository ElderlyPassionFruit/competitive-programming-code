import os

os.system("make j")
for i in range(10**6):
    a = os.system("./j")
    if (a != 0):
        print("RE", i)
        break
    print("OK", i)