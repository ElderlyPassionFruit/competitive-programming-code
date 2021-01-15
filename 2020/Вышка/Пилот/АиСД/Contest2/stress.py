import os

def gen(x):
    f = open("genIn", "w")
    print(x, file = f)

def main():
    os.system("make badD && make gen")
    bestLen = 1
    bestAns = 0
    for Len in range(240, 260):
        gen(Len)
        os.system("./gen < genIn > in")
        ans = 10**7
        Sum = 0
        for te in range(100):
            a = os.system("./badD < in > out")
            if (a != 0):
                print("RE", te)
                print("input = ")
                print(open("in", "r").read())
                break
            #print("OK", te)
            #continue
            out = int(open("out", "r").read())
            Sum += out
            if (ans > out):
                ans = out;
        ans = Sum / 100
        print(Len, ans / 10**7)
        if (ans > bestAns):
            bestLen = Len
            bestAns = ans
    print("bestLen =", bestLen, "bestAns =", bestAns)
main()