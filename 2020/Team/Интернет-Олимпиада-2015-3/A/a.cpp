#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));

const int MOD[2] = {998244353, (int)1e9 + 7};
const int base[2] = {(int)rnd() % 1000 + 1337 + 228, (int)rnd() % 1000 + 1337 + 228};
//const int base[2] = {2, 2};

int mul(int a, int b, int it) {
    return (ll) a * b % MOD[it];
}

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

const int A = 1e5 + 10;
int pows[2][A];

void initPows() {
    for (int it = 0; it < 2; ++it) {
        pows[it][0] = 1;
        for (int i = 1; i < A; ++i) {
            pows[it][i] = mul(pows[it][i - 1], base[it], it);
        }
    }
    /*cout << "pows = " << endl;
    for (int it = 0; it < 2; ++it) {
        for (int i = 0; i < 10; ++i) {
            cout << pows[it][i] << " ";
        }
        cout << endl;
    }*/
}

struct Hasher{
    pair<int, int> h;
    Hasher() {
        h = {0, 0};
    }
    void upd(int x, int cnt) {
        if (cnt == 1) {
            h.first = add(h.first, pows[0][x], 0);
            h.second = add(h.second, pows[1][x], 1);
        } else {
            h.first = sub(h.first, pows[0][x], 0);
            h.second = sub(h.second, pows[1][x], 1);
        }
    }
};

bool operator<(const Hasher& a, const Hasher& b) {
    return a.h < b.h;
}

const int N = 1e3 + 10;
int n, m;
int a[N], b[N];
map<Hasher, int> pos;

void initPos(int k) {
    pos.clear();
    Hasher have;
    for (int i = 0; i < k; ++i) {
        have.upd(a[i], 1);
    }
    pos[have] = 0;
    for (int i = k; i < n; ++i) {
        have.upd(a[i], 1);
        have.upd(a[i - k], -1);
        pos[have] = i - k + 1;
    }
    /*cout << "pos = " << endl;
    for (auto i : pos) {
        cout << i.first.h.first << " " << i.first.h.second << " " << i.second << endl;
    }*/
}

void solve(int k, int& ansK, int& ansI, int& ansJ) {
    Hasher have;
    for (int i = 0; i < k; ++i) {
        have.upd(b[i], 1);
    }
    if (pos.count(have)) {
        ansK = k;
        ansI = pos[have] + 1;
        ansJ = 1;
        return;
    }
    for (int i = k; i < m; ++i) {
        have.upd(b[i], 1);
        have.upd(b[i - k], -1);
        if (pos.count(have)) {
            ansK = k;
            ansI = pos[have] + 1;
            ansJ = i - k + 2;
            return;        
        }
    }    
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("anagrams2.in", "r", stdin);
    freopen("anagrams2.out", "w", stdout);
    initPows();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    int ansK = 0, ansI = -1, ansJ = -1;
	for (int k = 1; k <= min(n, m); ++k) {
        initPos(k);
        solve(k, ansK, ansI, ansJ);
    }
    cout << ansK << " " << ansI << " " << ansJ << "\n";
    return 0;
}










