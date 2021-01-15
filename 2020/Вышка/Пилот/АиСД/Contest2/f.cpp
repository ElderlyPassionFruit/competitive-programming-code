#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

mt19937 rnd(time(0));
const int MOD[2] = {998244353, (int)1e9 + 7};
const int base[2] = {(int)rnd() % 228 + 1337, (int)rnd() % 228 + 1337};

int add(int a, int b, int it) {
    a += b;
    if (a >= MOD[it]) return a - MOD[it];
    return a;
}

int sub(int a, int b, int it) {
    a -= b;
    if (a < 0) return a + MOD[it];
    return a;
}

int mul(int a, int b, int it) {
    return (ll) a * b % MOD[it];
}

const int N = 1e6 + 10;
int n, m;
vector<int> g[N];
int pows[2][N];

void read() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

void initPows() {
    for (int it = 0; it < 2; ++it) {
        pows[it][0] = 1;
        for (int i = 1; i < N; ++i) {
            pows[it][i] = mul(pows[it][i - 1], base[it], it);
        }
    }
}

pair<int, int> getHash(int v) {
    pair<int, int> ans = {0, 0};
    for (auto i : g[v]) {
        ans.first = add(ans.first, pows[0][i], 0);
        ans.second = add(ans.second, pows[1][i], 1);
    }
    return ans;
}

pair<int, int> myHash[N];
map<pair<int, int>, int> maphik;

void initHashs() {
    for (int i = 0; i < n; ++i) {
        myHash[i] = getHash(i);
        maphik[myHash[i]]++;
    }
}

ll ans;

pair<int, int> del(pair<int, int> a, int v) {
    a.first = sub(a.first, pows[0][v], 0);
    a.second = sub(a.second, pows[1][v], 1);
    return a;
}
    
void run() {
    initPows();
    initHashs();
    ans = 0;
    for (auto i : maphik) {
        ans += (ll)i.second * (i.second - 1) / 2;
    }
    for (int v = 0; v < n; ++v) {
        for (auto u : g[v]) {
            if (u < v) continue;
            if (del(myHash[v], u) == del(myHash[u], v)) {
                ++ans;
            }
        }
    }
}

void write() {
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}