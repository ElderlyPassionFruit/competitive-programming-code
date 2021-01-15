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
const ld eps = 1e-9;
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
 
const int MAXN = 30007;
bool ps[MAXN];
db res[MAXN];
db res2[MAXN];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
 
    for (int i = 2; i < MAXN; ++i) {
        if (!ps[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                ps[j] = 1;
            }
            //cout << i << endl;
            db val = log(i);
            for (int k = MAXN - 1; k >= i; --k) {
                db now = val;
                for (int t = i; k - t >= 0; t *= i) {
                    res[k] = max(res[k], res[k - t] + now);
                    now += val;
                }
                /*for (int t = 1; k - t * i >= 0 && t <= 2; ++t) {
                    res2[k] = max(res2[k], res2[k - t * i] + log(t * i));
                }*/
            }
        }
    }
 
    /*for (int i = 0; i < MAXN; ++i) {
        if (res[i] != res2[i]) {
            cout << i << ' ' << res[i] << ' ' << res2[i] << endl;
        }
    }*/
 
    for (int i = 1; i < MAXN; ++i) {
        res[i] = max(res[i], res[i - 1]);
    }
 
    cout << setprecision(10) << fixed;
 
    int T;
    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        cout << res[x] << '\n';
    }
    return 0;
}
 