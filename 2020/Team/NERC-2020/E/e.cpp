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

ll gcd(const ll& a, const ll& b, ll& x, ll& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll _x, _y, g = gcd(b, a % b, _x, _y);
    x = _y;
    y = _x - (a / b) * _y;
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    while (Q--) {
        ll t1, t2;
        cin >> t1 >> t2;

        ll a = t1, b = t2, c = t1 * t1;

        ll x, y;
        ll g = gcd(abs(a), abs(b), x, y);
        if (c % g != 0) {
            cout << 0 << '\n';
        } else {
            x *= c / g;
            y *= c / g;
            if (a < 0) {
                x *= -1;
            }
            if (b < 0) {
                y *= -1;
            }
            ll z = b / g, k;
            if (x > 0) {
                k = -x / z;
            } else {
                k = -x / z;
                if (x % z != 0) {
                    ++k;
                }
            }
            //cout << x << ' ' << y << ' ' << k << ' ' << z << '\n';
            x += b / g * k;
            y -= a / g * k;
            if (x == 0) {
                x += b / g;
                y -= a / g;
            }
            cout << (max(y, 0ll) + a / g - 1) / (a / g) << '\n';
        }
    }
    return 0;
}
