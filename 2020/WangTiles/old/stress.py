import os

def main():
    os.system("make main && make gen")
    maxA = 0
    maxB = 0
    for te in range(10**6):
        os.system("./gen > in")
        a = os.system("./main < in > out")
        if (a != 0):
            print("RE", te)
            print("input = ")
            print(open("in", "r").read())
            break
        #print("OK", te)
        #continue
        out = open("out", "r").read()
        x = int(out.split()[0]);
        y = int(out.split()[1]);
        if (x > maxA):
            maxA = x;
        if (y > maxB):
            maxB = y
        if (x == 3 and y == 3):
            print(open("in", "r").read())
            return
        print(te, x, y, maxA, maxB)
        #os.system("./stupid < in > out")
        #ans = open("out", "r").read()
        #print(ans, out)
        #if (ans != out):
        #    print("WA", te)
        #    print("input = ")
        #    print(open("in", "r").read())
        #    print("out = ")
        #    print(out)
        #    print("ans = ")
        #    print(ans)
        #    break
        #print("OK", te)
main()