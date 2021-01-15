#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e6 + 10, A = 26;

int n;
string s;
int pref[N][A];
int q;

void build() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < A; ++j) {
            pref[i][j] = pref[i - 1][j];
        }
        pref[i][s[i - 1] - 'a']++;
    }
}

int get(int l, int r, int a) {
    return pref[r][a] - pref[l - 1][a];
}

int get(int l, int r) {
    bool one = false;
    int sum = 0;
    for (int i = 0; i < A; ++i) {
        int x = get(l, r, i);
        sum += x - x % 2;
        if (x & 1) {
            one = true;
        }
    }
    if (one) {
        ++sum;
    }
    return sum;
}

void solve(int l, int r) {
    int nowL = l, nowR = r;
    int val = get(l, r);
    for (int myL = l; myL <= min(r, l + 26); ++myL) {
        for (int myR = max(myL, r - 26); myR <= r; ++myR) {
            int have = get(myL, myR);
            if ((ll)val * val * (myR - myL + 1) < (ll)have * have * (nowR - nowL + 1)) {
                nowL = myL;
                nowR = myR;
                val = have;
            }
        }
    }
    cout << nowL << " " << nowR << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> s >> q;
    build();
    while (q--) {
        int l, r;
        cin >> l >> r;
        solve(l, r);
    }
	return 0;
}