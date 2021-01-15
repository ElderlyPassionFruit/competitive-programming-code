#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct Point{
    int x, y;
    Point() {}
    Point(int _x, int _y)
        : x(_x)
        , y(_y)
    {
    }
};

bool operator<(const Point& a, const Point& b) {
    return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(const Point& a, const Point& b) {
    return tie(a.x, a.y) == tie(b.x, b.y);
}

Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

ll operator^(const Point& a, const Point& b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
}

int sign(ll x) {
    if (x == 0) return 0;
    if (x > 0) return 1;
    return -1;
}

bool checkOnLine(const Point& a, const Point& b, const Point& x) {
    return sign((b - a) ^ (x - a)) == 0;
}

const int N = 1e5 + 10;
int n, k;
Point p[N];
const int K = 9;
Point base[2 * K + 10];
int topBase;
pair<int, int> ans[K];
int topAns;
bool found;

void read() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p, p + n);
    n = unique(p, p + n) - p;
}

void build() {
    topAns = 0;
    found = false;
    topBase = 0;
    for (int i = 0; i < n && topBase <= 2 * k; ++i) {
        bool ok = false;
        for (int x = 0; x < topBase && !ok; ++x) {
            for (int y = x + 1; y < topBase && !ok; ++y) {
                if (checkOnLine(base[x], base[y], p[i])) {
                    ok = true;
                }
            }
        }
        if (!ok) {
            base[topBase++] = p[i];
        }
    }
}

void check() {
    for (int i = 0; i < n; ++i) {
        bool ok = false;
        for (int line = 0; line < k; ++line) {
            if (checkOnLine(base[ans[line].first], base[ans[line].second], p[i])) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            return;
        }
    }
    found = true;
}

// int getInd(int bit1, int bit2) {
//     int cnt = 0;
//     for (int x = 0; x < topBase; ++x) {
//         for (int y = 0; y < x; ++y) {
//             if (x == bit2 && y == bit1) return cnt;
//             cnt++;
//         }
//     }
//     return -1;
// }

void rec(ll used, int cnt) {
    if (cnt == k && !found) {
        check();
        return;
    }
    for (int bit1 = 0; bit1 < topBase && !found; ++bit1) {
        if ((used >> bit1) & 1) continue;
        for (int bit2 = bit1 + 1; bit2 < topBase && !found; ++bit2) {
            int ind = bit2 * (bit2 - 1) / 2 + bit1;            
            // assert(ind == getInd(bit1, bit2));
            if ((used >> ind) & 1) continue;
            used ^= (1LL << ind);
            ans[topAns] = {bit1, bit2};
            ++topAns;
            rec(used, cnt + 1);
            if (found) break;
            used ^= (1LL << ind);
            --topAns;
        }
    }
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    rec(0, 0);
}

void run() {
    ld start_time = clock();
    found = false;
    while (((ld)clock()- start_time) / CLOCKS_PER_SEC < 0.15 && !found) {
        shuffle(p, p + n, rnd);
        build();
        // cerr << "topBase = " << topBase << endl;
        // cerr << "base = " << endl;
        // for (int i = 0; i < topBase; ++i) {
        //     cerr << base[i].x << " " << base[i].y << endl;
        // }
        if (topBase > 2 * k) return;
        solve();
    }
}

void write() {
    if (found) {
        cout << "Yes\n";
        cout << topAns << '\n';
        for (int i = 0; i < topAns; ++i) {
            cout << base[ans[i].first].x << " " << base[ans[i].first].y << " " << base[ans[i].second].x << " " << base[ans[i].second].y << '\n'; 
        }
    } else {
        cout << "No\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    int t;
    cin >> t;
    while (t--) {
        read();
        run();
        write();
    }
    return 0;
}