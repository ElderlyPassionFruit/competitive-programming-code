#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

string s;
ll MOD;
int base;

ll add(ll a, ll b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

ll sub(ll a, ll b) { 
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

void read() {
    cin >> s >> MOD >> base;
}

ll calcHash(const string& s) {
    ll ans = 0;
    for (const auto c : s) {
        ans = add(mul(ans, base), c);
    }
    return ans;
}

const int BUBEN = 4;
const int SZ = 1e6;
string allC;

unordered_map<ll, string> hashes;

void gen(string& s) {
    if (hashes.size() == SZ) return;
    if (s.size() == BUBEN) {
        hashes[calcHash(s)] = s;
        return;
    }
    for (const auto i : allC) {
        s += i;
        gen(s);
        s.pop_back();
    }
}

void init() {
    allC = "";
    for (int i = 0; i < 26; ++i) {
        allC += 'a' + i;
    }
    for (int i = 0; i < 26; ++i) {
        allC += 'A' + i;
    }
    for (int i = 0; i < 10; ++i) {
        allC += '0' + i;
    }
    allC += '_';
    hashes.max_load_factor(0.25);
    hashes.reserve(SZ);
    string myS = "";
    gen(myS);
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

string ans;
ll need;

bool trySolve() {
    string fans = "";
    for (int i = 0; i < 14 - BUBEN; ++i) {
        fans += allC[(ll)rnd() % allC.size()];
    }
    ll have = calcHash(fans); 
    for (int i = 0; i < BUBEN; ++i) {
        have = mul(have, base);
    }
    ll x = sub(need, have);
    if (hashes.find(x) == hashes.end()) return false;
    ans = fans + hashes[x];
    return true;
}

void run() {
    need = calcHash(s);
    init();
    ans = "";
    while (!trySolve()) {
    }
}

void write() {
    cout << ans;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}