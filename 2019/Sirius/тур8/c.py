import time
def main():
    f = open("board.in", "r")
    start = time.time()
    s = f.readline()
    t = f.readline()
    ans = 0;
    cntU = 0
    cntD = 0;

    for i in s:
        if i == '1' or i == '2':
            cntD += 1
        elif i == 'U':
            cntU += 1
    l_s = cntD - cntU;

    cntU = 0
    cntD = 0;

    for i in t:
        if i == '1' or i == '2':
            cntD += 1
        elif i == 'U':
            cntU += 1
    l_t = cntD - cntU;
    flag = max(l_t, l_s) > 50
    ans += abs(l_s - l_t)

    while (l_s > l_t):
        s += "U"
        l_s -= 1

    while (l_t > l_s):
        t += "U"
        l_t -= 1

    v_s = 1;

    for i in s:
        if i == '1':
            v_s = v_s * 2
        elif i == '2':
            v_s = v_s * 2 + 1
        elif i == 'U':
            v_s //= 2
        elif i == 'L':
            v_s -= 1
        elif i == 'R':
            v_s += 1

    v_t = 1;

    for i in t:
        if i == '1':
            v_t = v_t * 2
        elif i == '2':
            v_t = v_t * 2 + 1
        elif i == 'U':
            v_t //= 2
        elif i == 'L':
            v_t -= 1
        elif i == 'R':
            v_t += 1

    fans = abs(v_s - v_t)
    if (fans == 0):
        print(ans, file = open("board.out", "w"))
        return
        
    need = 0;
    while (v_s > 0 and v_t > 0):
        help = need + abs(v_s - v_t)
        fans = min(fans, help)
        need += 2
        v_s //= 2
        v_t //= 2
    ans += fans;

    print(ans, file = open("board.out", "w"))
main()