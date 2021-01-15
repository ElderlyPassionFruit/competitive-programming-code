#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

uint32_t x0, x1, a, b, c;

uint32_t next() {  
    uint32_t t = x0 * a + x1 * b + c;  
    x0 = x1;  
    x1 = t;  
    return x0 >> 2;  
}

int n, q;

void read() {
    cin >> n >> q >> x0 >> x1 >> a >> b >> c;
}

uint32_t ans;
const uint32_t p = 10099;
uint32_t now = 1;

const int B = 10;
int BUBEN = B;

int pos[B];
uint32_t val[B];

void relax() {
    int x = next() % n;
    int myVal = next();
    //cout << x << " " << myVal << endl;
    bool ok = true;
    for (int i = 0; i < BUBEN; ++i) {
        if (pos[i] == x) {
            val[i] = myVal;
            ok = false;
            break;
        }
    }
    if (ok) {
        if (val[BUBEN - 1] > myVal) {
            pos[BUBEN - 1] = x;
            val[BUBEN - 1] = myVal;
        }
    }
    for (int i = 1; i < BUBEN; ++i) {
        if (val[i] < val[i - 1]) {
            swap(pos[i], pos[i - 1]);
            swap(val[i], val[i - 1]);
        }
    }
    for (int i = BUBEN - 1; i > 0; --i) {
        if (val[i] < val[i - 1]) {
            swap(pos[i], pos[i - 1]);
            swap(val[i], val[i - 1]);
        }
    }
}

uint32_t get() {
    return val[0];
}

void run() {
    BUBEN = min(BUBEN, n);
    iota(pos, pos + BUBEN, 0);
    fill(val, val + BUBEN, (1LL << 31) - 1);
    ans = 0;
    for (int i = 0; i < q; ++i) {
        relax();
        now *= p;
        //cout << get() << endl;
        ans += get() * now;
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