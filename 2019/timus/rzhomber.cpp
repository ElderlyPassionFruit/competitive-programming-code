#include <bits/stdc++.h>
 
#define ll long long
#define ull unsigned ll
#define vi vector<ll>
#define vvi vector<vi>
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define ld long double
#define pii pair<ll, ll>
#define mt make_tuple
#define mn(a, b) a = min(a, b)
#define mx(a, b) a = max(a, b)
 
using namespace std;
 
const ll INF = (ll)2e9;
const ll inf = (ll)2e18;
const ld eps = (ld)1e-8;
const ll mod = (ll)998244353;
const ll MAXN = (ll)4e5 + 1;
const ll MAXC = (ll)1e6 + 1;
const ll MAXE = (ll)1000;
const ll MAXLOG = 21;
const ll maxlen = (ll)1e5;
const ll asci = (ll)256;
const ll block = 480;
const ld PI = acos(-1);
const ld e = 2.7182818284;
 
template <class T>
istream& operator >>(istream &in, vector<T> &arr){
    for (T &cnt : arr) {
        in >> cnt;
    }
    return in;
};

ll p;

ll fast_pow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) { 
            ans = ans * x % p;
        }
        x = x * x % p;
        y >>= 1;
    }
    return ans;
}

void solve() {
    ll n; cin >> p >> n;
    vi vals, G(n); vvi tests(n);
    for (ll i = 0; i < n; ++i) {
        ll cnt; cin >> cnt;
        tests[i].resize(cnt); cin >> tests[i];
        for (ll j = 0; j < cnt; ++j) vals.push_back(tests[i][j]);
        cin >> G[i];
    }
    for (ll i = 0; i < n; ++i) vals.push_back(G[i]);
    sort(all(vals));
    vals.resize(unique(all(vals)) - vals.begin());
    vi ans(vals.size(), 1);
    vi primes;
    ll pn = p - 1;
    for (ll i = 2; i * i <= pn; ++i) {
        while (pn % i == 0) primes.push_back(i), pn /= i;
    }
    if (pn > 1) primes.push_back(pn);
    sort(all(primes));
    primes.resize(unique(all(primes)) - primes.begin());
    vi st(primes.size(), 0);
    pn = p - 1;
    for (ll i = 0; i < primes.size(); ++i) {
        while (pn % primes[i] == 0) st[i]++, pn /= primes[i];
    }
    for (ll i = 0; i < vals.size(); ++i) {
        for (ll j = 0; j < primes.size(); ++j) {
            int val = primes[j];
            for (int k = 0; k < st[j]; ++k) {
                if (fast_pow(vals[i], (p - 1) / val) == 1) ans[i] *= primes[j], val *= primes[j];
                else break;
            }
        }
    }
    for (ll i = 0; i < n; ++i) {
        ll gcd = ans[lower_bound(all(vals), tests[i][0]) - vals.begin()];
        for (ll j = 0; j < tests[i].size(); ++j) {
            gcd = __gcd(gcd, ans[lower_bound(all(vals), tests[i][j]) - vals.begin()]);
        }
        if (ans[lower_bound(all(vals), G[i]) - vals.begin()] % gcd == 0) cout << "1\n";
        else cout << "0\n";
    }
}

int main() {
    srand(time(0));
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    cout.precision(30);
    solve();
 
    return 0;
}