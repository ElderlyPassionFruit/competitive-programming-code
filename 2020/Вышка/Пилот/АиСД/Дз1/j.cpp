#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;
#define list List

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

struct Node{
    int l, r, u, d;
    Node() {
        l = -1, r = -1, u = -1, d = -1;
    }
    Node(int _l, int _r, int _u, int _d) {
        l = _l, r = _r, u = _r, d = _d;
    }
};

const int N = 2000 + 228;
const int MEM = 2000 * 2000 + 4000 + 228;
Node list[MEM];

int n, m, k;
int indL[N], indU[N];

void read() {
    cin >> n >> m >> k;
}

int getInd(int x, int y) {
    return x * m + y;
}

bool checkCell(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void build() {
    for (int x = 0; x < n; ++x) {
        indL[x] = getInd(x, 0);
    }
    for (int y = 0; y < m; ++y) {
        indU[y] = getInd(0, y);
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            int ind = getInd(x, y);
            int l = (checkCell(x, y - 1) ? getInd(x, y - 1) : -1);
            int r = (checkCell(x, y + 1) ? getInd(x, y + 1) : -1);
            int u = (checkCell(x - 1, y) ? getInd(x - 1, y) : -1);
            int d = (checkCell(x + 1, y) ? getInd(x + 1, y) : -1);
            list[ind] = {l, r, u, d};
        }
    }
}

void changeV(int x1, int y1, int x2, int y2) {
    int leftUpCorner = indL[x1];
    for (int i = 0; i < y1; ++i) {
        
    }
    if (y1 == 0) {

    } else {

    }
}

void changeH(int x1, int y1, int x2, int y2) {

}

void run() {
    build();
    while (k--) {
        char t;
        int x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        --x1;
        --y1;
        --x2;
        --y2;
        if (t == 'V') {
            changeV(x1, y1, x2, y2);
        } else {
            changeH(x1, y1, x2, y2);
        }
    }
}

void write() {
    for (int i = 0; i < n; ++i) {
        int now = indL[i];
        int last = 0;
        for (int j = 0; j < m; ++j) {
            assert(now != -1);
            cout << now << ' ';
            int nxtLast = now;
            if (list[now].l == -1) {
                now = list[now].r;
            } else if (list[now].r == -1) {
                now = list[now].l;
            } else {
                now = list[now].l ^ list[now].r ^ last;
            }
            last = nowLast;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}