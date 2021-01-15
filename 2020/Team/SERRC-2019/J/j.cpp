#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;
const int N = 2e6 + 7;
int r[N], f[N], rf[N];

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int binpow(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) {
            ans = mul(ans, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return ans;
}

int getInv(int a) {
    return binpow(a, MOD - 2);
}

void initFact() {
    f[0] = rf[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = mul(f[i - 1], i);
        rf[i] = getInv(f[i]);
    }
    for (int i = 1; i < N; ++i) {
        r[i] = getInv(i);
    }
}

int c(int n, int k) {
    if (n < k || k < 0) return 0;
    return mul(mul(f[n], rf[k]), rf[n - k]);
}

int cat(int n) {
    return mul(c(n << 1, n), r[n + 1]);
}

int n;
int a[N / 2];

const int LOG = 20;

int lg[N / 2];
int sparse[N / 2][LOG];

void build() {
    for (int i = 2; i <= n; ++i) {
        lg[i] = lg[i / 2] + 1;
    }
    for (int i = 0; i < n; ++i) {
        sparse[i][0] = i;
    }
    for (int l = 1; l < LOG; ++l) {
        for (int i = 0; i + (1 << l) - 1 < n; ++i) {
            //sparse[i][l] = min(sparse[i][l - 1], sparse[i + (1 << (l - 1))][l - 1]);
            if (a[sparse[i][l - 1]] <= a[sparse[i + (1 << (l - 1))][l - 1]]) {
                sparse[i][l] = sparse[i][l - 1];
            } else {
                sparse[i][l] = sparse[i + (1 << (l - 1))][l - 1];
            }
        }
    }
}

int getMin(int l, int r) {
    int log = lg[r - l];
    if (a[sparse[l][log]] <= a[sparse[r - (1 << log) + 1][log]]) {
        return sparse[l][log];
    } else {
        return sparse[r - (1 << log) + 1][log];
    }
    /*int ans = l;
    for (int i = l + 1; i <= r; ++i) {
        if (a[ans] > a[i]) {
            ans = i;
        }
    }
    return ans;*/
}

int solve(int l, int r) {
    //cout << "l = " << l << " r = " << r << endl;
    if (l >= r) return 1;
    int pos = getMin(l, r);
    int myMul = 1;
    myMul = mul(myMul, solve(l, pos - 1));
    int cnt = 1;
    while (pos < r) {
        int nPos = getMin(pos + 1, r);
        if (a[pos] != a[nPos]) break;
        myMul = mul(myMul, solve(pos + 1, nPos - 1));
        pos = nPos;
        ++cnt;
    }
    //cout << "cnt = " << cnt << " l = " << l << " r = " << r << endl;
    myMul = mul(myMul, solve(pos + 1, r));
    return mul(myMul, cat(cnt));
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    initFact();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build();
    cout << solve(0, n - 1) << "\n";
    return 0;
}