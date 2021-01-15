#include <bits/stdc++.h>

#define f first
#define s second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ll long long
#define ull unsigned long long
#define db double
#define ld long double
#define pii pair<int, int>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define px pair<db, db>
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define input(a) for (auto& el : a) cin >> el;
#define output(a) cout << '!'; for (auto& el : a) cout << el << ' '; cout << '\n'; cout.flush();
#define sz(el) int(el.size())
#define sq(a) ((a) * (a))
#define xll __int128
#define xmin(a,b) a = min(a, b)
#define xmax(a,b) a = max(a, b)
#define sun(a) sort(all(a)); a.resize(unique(all(a)) - a.begin());

using namespace std;

template <class T1, class T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
    return (out << p.f << ' ' << p.s << endl);
}

const int INF = 1000000017;
const ll LLINF = 1000000000000000017LL;
const ld inf = 1.0 / 0.0;
const ld eps = 1e-10;
const int MOD = 1e9 + 7;
const int MOD2 = 1e9 + 9;

//mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//uniform_int_distribution<int> uid(l, r); [l, r]
//int x = uid(rng);

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tret;

/// *find_by_order - val by index, order_of_key - # less than x
*/

/// Author: @mathalex
namespace modint {
    static const int MODx = 1e9 + 7;

    struct mint {
        int a = 0;

        mint() {}

        mint(int a) : a(a) {
            /// a = (a % MODx + MODx) % MODx;
        }

        mint operator-() const {
            if (a) {
                return -a + MODx;
            } else {
                return 0;
            }
        }

        mint operator+(const mint& b) const {
            int res = a + b.a;
            if (res >= MODx) {
                res -= MODx;
            }
            return res;
        }

        void operator+=(const mint& b) {
            a += b.a;
            if (a >= MODx) {
                a -= MODx;
            }
        }

        mint operator-(const mint& b) const {
            int res = a - b.a;
            if (res < 0) {
                res += MODx;
            }
            return res;
        }

        void operator-=(const mint& b) {
            a -= b.a;
            if (a < 0) {
                a += MODx;
            }
        }

        mint operator*(const mint& b) const {
            return (ll) a * b.a % MODx;
        }

        void operator*=(const mint& b) {
            a = (ll) a * b.a % MODx;
        }

        int get() const {
            return a;
        }
    };

    mint fpow(mint a, int p) {
        mint x = 1;
        while (p) {
            if (p & 1) {
                x *= a;
            }
            a *= a;
            p >>= 1;
        }
        return x;
    }

    istream& operator>>(istream& in, mint& a) {
        return (in >> a.a);
    }

    ostream& operator<<(ostream& out, const mint& a) {
        return (out << a.a);
    }
}

using namespace modint;

const int N = 1e6 + 7;
mint f[N], rf[N];

mint c(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    return f[n] * rf[n - k] * rf[k];
}

mint get(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        return 0;
    }

    bool re2 = 0;
    if (y1 > y2) {
        swap(x1, x2);
        swap(y1, y2);
        re2 = 1;
    }
    re2 ^= (x1 > x2);
    bool re = (x1 > x2);

    int mn = min(x1, x2), mx = max(x1, x2);
    //cout << mn << ' ' << mx << endl;

    ///cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
    mint res = 0;

    int L = 0, R = -1;
    mint pr = 0;

    int sx = x1, sy = y1;
    int g = gcd(abs(x2 - x1), abs(y2 - y1));
    int vx = (x2 - x1) / g, vy = (y2 - y1) / g;
    while (1) {
        //cout << sx << ' ' << sy << endl;
        sx += vx;
        sy += vy;

        if (sx == x2 && sy == y2) {
            break;
        }
        //cout << sx << ' ' << sy << endl;
        if (sy >= 0 && sx >= -sy && sx <= sy && (sx + sy) % 2 == 0) {
            res -= c(sy, (sx + sy) / 2);
        }
    }

    for (int i = 0; i < N; ++i) {
        if (i > y2) {
            break;
        }

        if (i <= y1 && x1 >= -i && x1 <= i && (x1 + i) % 2 == 0) {
            res -= c(i, (x1 + i) / 2);
        }

        if (i <= y2 && x2 >= -i && x2 <= i && (x2 + i) % 2 == 0) {
            res -= c(i, (x2 + i) / 2);
        }

        int cx1 = mn, cx2 = mx;

        if (y1 != y2 && i >= y1) {
            ll cur = 1ll * (i - y1) * (x2 - x1), d = y2 - y1;
            if (re) {
                cx2 = cur / d + x1;
                /*if (cur % d == 0) {
                    --cx2;
                }*/
            } else {
                cx1 = (cur + d - 1) / d + x1;
                /*if (cur % d == 0) {
                    ++cx1;
                }*/
            }
        }
        /*if (i < 5) {
            cout << i << ' ' << cx1 << ' ' << cx2 << endl;
        }*/

        xmax(cx1, -i);
        xmin(cx2, i);

        int cl = (cx1 + i + 1) / 2, cr = i - (i - cx2 + 1) / 2;
        //cout << cl << ' ' << cr << endl;
        if (cl > cr) {
            continue;
        }

        int op1 = abs(cl - L) + abs(cr - R), op2 = cr - cl + 1;
        if (op1 < op2 && L <= R) {
            pr *= 2;
            pr += c(i - 1, L - 1) + c(i - 1, R + 1);
            ++R;
            //cout << pr << ' ' << L << ' ' << R << endl;

            while (L < cl) {
                pr -= c(i, L);
                ++L;
            }

            while (L > cl) {
                --L;
                pr += c(i, L);
            }

            while (R < cr) {
                ++R;
                pr += c(i, R);
            }

            while (R > cr) {
                pr -= c(i, R);
                --R;
            }
            res += pr;
            //cout << '@' << pr << ' ' << L << ' ' << R << endl;
        } else {
            L = cl;
            R = cr;
            pr = 0;
            for (int j = L; j <= R; ++j) {
                pr += c(i, j);
            }
            //cout << pr << endl;
            res += pr;
        }
    }

    if (re2) {
        res *= MODx - 1;
    }
    ///cout << '!' << re2 << ' ' << res << endl;
    return res;
}

struct Vector {
    ll x = 0, y = 0;

    Vector() {}

    Vector(ll x, ll y) : x(x), y(y) {}
};

Vector operator-(const Vector& a, const Vector& b) {
    return {a.x - b.x, a.y - b.y};
}

ll operator*(Vector& a, Vector& b) {
    return a.x * b.x + a.y * b.y;
}

ll operator%(Vector& a, Vector& b) {
    return a.x * b.y - a.y * b.x;
}

ld angle(Vector& a, Vector& b) {
    //cout << atan2(a % b, a * b) << endl;
    return atan2(a % b, a * b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    f[0] = rf[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = f[i - 1] * i;
        rf[i] = rf[i - 1] * fpow(i, MODx - 2);
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        mint cur = get(x1, y1, x2, y2) + get(x2, y2, x3, y3) + get(x3, y3, x1, y1);

        bool re = 1;
        int mny = min(y1, min(y2, y3));
        if (y1 == mny) {
            re = (x2 > x3);
        } else if (y2 == mny) {
            re = (x3 > x1);
        } else {
            re = (x1 > x2);
        }
        if (re) {
            cur *= MODx - 1;
        }

        /*vector<pii> tmp;
        vector<pii> xs = {mp(x1, y1), mp(x2, y2), mp(x3, y3)};
        for (int i = 0; i < N; ++i) {
            for (pii& p : xs) {
                int x = p.f, y = p.s;
                if (i <= y && x >= -i && x <= i && (x - i) % 2 == 0) {
                    Vector v1(x1 - x, y1 - i), v2(x2 - x, y2 - i), v3(x3 - x, y3 - i);
                    ld s = angle(v1, v2) + angle(v2, v3) + angle(v3, v1);

                    bool ok = 0;
                    for (int i = 0; i < 3; ++i) {
                        if (1ll * (x - xs[i].f) * (xs[(i + 1) % 3].s - i) == 1ll * (i - xs[i].s) * (xs[(i + 1) % 3].f - x)) {
                            ok = 1;
                            break;
                        }
                    }
                    if (abs(s) > eps || ok) {
                        tmp.eb(i, x);
                        //cout << i << ' ' << x << ' ' << s << endl;
                    }
                }
            }
        }*/

        //cout << cur << endl;

        //cout << "cur = " << cur << endl;

        vector<pii> xs = {mp(x1, y1), mp(x2, y2), mp(x3, y3)};
        for (int i = 0; i < 3; ++i) {
            int x1 = xs[i].f, y1 = xs[i].s, x2 = xs[(i + 1) % 3].f, y2 = xs[(i + 1) % 3].s;
            int sx = x1, sy = y1;
            int g = gcd(abs(x2 - x1), abs(y2 - y1));
            int vx = (x2 - x1) / g, vy = (y2 - y1) / g;
            while (1) {
                //cout << sx << ' ' << sy << endl;
                sx += vx;
                sy += vy;

                //cout << sx << ' ' << sy << endl;
                if (sy >= 0 && sx >= -sy && sx <= sy && (sx + sy) % 2 == 0) {
                    int cnt = 0;
                    for (int i = 0; i < 3; ++i) {
                        int cx1 = xs[i].f, cy1 = xs[i].s, cx2 = xs[(i + 1) % 3].f, cy2 = xs[(i + 1) % 3].s;
                        if (cx1 > cx2) {
                            swap(cx1, cx2);
                            swap(cy1, cy2);
                        }
                        Vector v1 = Vector(cx2, cy2) - Vector(cx1, cy1);
                        Vector v2 = Vector(sx, sy) - Vector(cx1, cy1);
                        if (sx > cx1 && sx < cx2 && v1 % v2 < 0) {
                            cnt++;
                        }
                    }
                    if (cnt % 2 != 1) {
                        cur += c(sy, (sx + sy) / 2);
                    }
                }
                if (sx == x2 && sy == y2) {
                    break;
                }
            }
        }

        sort(xs.begin(), xs.end());

        for (int y = 0; y < xs[1].second; ++y) {
            int x = xs[1].first;
            //cout << x << " " << y << endl;
            Vector v1 = Vector(xs[2].first, xs[2].second) - Vector(xs[0].first, xs[0].second);
            Vector v2 = Vector(x, y) - Vector(xs[0].first, xs[0].second);
            if (v2 % v1 < 0) {
                if (y >= 0 && x >= -y && x <= y && (x + y) % 2 == 0) {
                    cur += c(y, (x + y) / 2);
                }
            }
        }

        cout << cur << '\n';
    }
    return 0;
}
