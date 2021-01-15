#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int MOD;

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

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

int l, r;

const int B = sqrt(2e7);
int suffMul[B + 10];

void build(int L, int R) {
    for (int i = 0; i <= R - L; ++i) {
        suffMul[i] = i + L;
    }
    for (int i = 1; i <= R - L; ++i) {
        suffMul[R - L - i] = mul(suffMul[R - L - i], suffMul[R - L - i + 1]);
    }
    suffMul[R - L + 1] = 1;
}

int calc(int l, int r) {
    int ans = 1;
    for (int i = l; i <= r; ++i) {
        ans = mul(ans, i);
    }
    return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> l >> r >> MOD;
    int allMul = calc(l, r);
    int sum = 0;
    for (int L = l; L <= r; L += B) {
        int R = min(r, L + B - 1);
        build(L, R);
        int nowMul = mul(getInv(calc(L, R)), allMul);
        for (int i = L; i <= R; i++) {
            sum = add(sum, mul(nowMul, suffMul[i - L + 1]));
            nowMul = mul(nowMul, i);
        }
    }
    cout << mul(sum, getInv(allMul)) << endl;
	return 0;
}