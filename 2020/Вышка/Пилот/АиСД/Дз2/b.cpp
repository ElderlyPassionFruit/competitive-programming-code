#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1e3 + 10;
int n, m;
string a[N];
int h, w;
string b[N];

void read() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    } 
    cin >> h >> w;
    for (int i = 0; i < h; ++i) {
        cin >> b[i];
    }
}

mt19937 rnd(time(0));
const int MOD = 998244353;
const int base[2] = {(int)rnd() % 228 + 1337, (int)rnd() % 228 + 1337};

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int hA[N][N], hB[N][N];
int pows[2][N];

void initH() {
    for (int it = 0; it < 2; ++it) {
        pows[it][0] = 1;
        for (int i = 1; i < N; ++i) {
            pows[it][i] = mul(pows[it][i - 1], base[it]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int fans = 0;
            fans = add(fans, mul(hA[i - 1][j], base[0]));
            fans = add(fans, mul(hA[i][j - 1], base[1]));
            fans = sub(fans, mul(hA[i - 1][j - 1], mul(base[0], base[1])));
            fans = add(fans, a[i - 1][j - 1]);
            hA[i][j] = fans;
        }
    }
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            int fans = 0;
            fans = add(fans, mul(hB[i - 1][j], base[0]));
            fans = add(fans, mul(hB[i][j - 1], base[1]));
            fans = sub(fans, mul(hB[i - 1][j - 1], mul(base[0], base[1])));
            fans = add(fans, b[i - 1][j - 1]);
            hB[i][j] = fans;
        }
    }
}

int getA(int x1, int y1, int x2, int y2) {
    assert(x1 <= x2);
    assert(y1 <= y2);
    int ans = hA[x2][y2];
    ans = sub(ans, mul(hA[x1 - 1][y2], pows[0][x2 - x1 + 1]));
    ans = sub(ans, mul(hA[x2][y1 - 1], pows[1][y2 - y1 + 1]));
    ans = add(ans, mul(hA[x1 - 1][y1 - 1], mul(pows[0][x2 - x1 + 1], pows[1][y2 - y1 + 1])));
    return ans;
}

int getB(int x1, int y1, int x2, int y2) {
    assert(x1 <= x2);
    assert(y1 <= y2);
    int ans = hB[x2][y2];
    ans = sub(ans, mul(hB[x1 - 1][y2], pows[0][x2 - x1 + 1]));
    ans = sub(ans, mul(hB[x2][y1 - 1], pows[1][y2 - y1 + 1]));
    ans = add(ans, mul(hB[x1 - 1][y1 - 1], mul(pows[0][x2 - x1 + 1], pows[1][y2 - y1 + 1])));
    return ans;
}

bool checkSame(int x1, int y1, int x2, int y2, int lenX, int lenY) {
    if (lenX == 0 || lenY == 0) return true;
    return getA(x1, y1, x1 + lenX - 1, y1 + lenY - 1) == getB(x2, y2, x2 + lenX - 1, y2 + lenY - 1);
}

bool checkSame(int x1, int y1, int lenX, int lenY) {
    if (lenX == h && lenY == w) return true;
    if (lenX > 0 && !checkSame(x1, y1, 1, 1, lenX, w)) return false;
    if (lenX + 2 <= n && !checkSame(x1 + lenX + 1, y1, lenX + 2, 1, h - lenX - 1, w)) return false;
    if (lenY > 0 && !checkSame(x1, y1, 1, 1, h, lenY)) return false;
    if (lenY + 2 <= w && !checkSame(x1, y1 + lenY + 1, 1, lenY + 2, h, w - lenY - 1)) return false;
    return true; 
}

int check(int x, int y) {
    int Ldx = -1, Rdx = h;
    while (Ldx < Rdx - 1) {
        int mid = (Ldx + Rdx) / 2;
        if (checkSame(x, y, 1, 1, mid + 1, w)) {
            Ldx = mid;
        } else {
            Rdx = mid;
        }
    }
    int lenX = Ldx + 1;
    int Ldy = -1, Rdy = w;
    while (Ldy < Rdy - 1) {
        int mid = (Ldy + Rdy) / 2;
        if (checkSame(x, y, 1, 1, h, mid + 1)) {
            Ldy = mid;
        } else {
            Rdy = mid;
        }
    }
    int lenY = Ldy + 1;
    return checkSame(x, y, lenX, lenY);
}

int ans;

void run() {
    initH();
    ans = 0;
    for (int x = 1; x + h - 1 <= n; ++x){
        for (int y = 1; y + w - 1 <= m; ++y) {
            ans += check(x, y);
        }
    }
}

void write() {
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}