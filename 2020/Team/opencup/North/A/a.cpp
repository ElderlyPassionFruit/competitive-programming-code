#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));
const int MOD[2] = {998244353, (int)1e9 + 7};
const int base[2] = {(int)rnd() % 228 + 1337, (int)rnd() % 228 + 1337};
//const int base[2] = {2, 2};

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

const int N = 2e5 + 10;
int n;
int a[N];

int pows[2][N];
int h[2][N];

void init() {
    for (int it = 0; it < 2; ++it) {
        pows[it][0] = 1;
        h[it][0] = 0;
        for (int i = 1; i <= 2 * n; ++i) {
            pows[it][i] = mul(pows[it][i - 1], base[it], it);
            h[it][i] = add(mul(h[it][i - 1], base[it], it), a[i - 1], it);
        }
    }
}

pair<int, int> get(int l, int r) {
    return {
        sub(h[0][r], mul(h[0][l - 1], pows[0][r - l + 1], 0), 0),
        sub(h[1][r], mul(h[1][l - 1], pows[1][r - l + 1], 1), 1)
    };
}

void solve() {
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    set<pair<int, int>> fans;
    init();
    for (int i = 1; i <= n; ++i) {
        //auto have = get(i, i + n - 1);
        fans.insert(get(i, i + n - 1));
        //cout << have.first << " " << have.second << endl;
    }
    reverse(a, a + 2 * n);
    init();
    for (int i = 1; i <= n; ++i) {
        fans.insert(get(i, i + n - 1));
    }
    cout << fans.size() << '\n';
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    while (cin >> n) {
        solve();
    }
	return 0;
}