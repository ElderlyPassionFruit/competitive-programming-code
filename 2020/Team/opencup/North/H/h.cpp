#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

int n, m;

const int MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
const int MAXK = 18;

ll pows[MAXN];
ll coun1[1 << MAXK];
ll coun2[1 << MAXK];


void precalc() {
    pows[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pows[i] = (pows[i - 1] * 2) % MOD;
    }
}

void solve() {


    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int need = 1;
    while (pows[need] < n) {
        need++;
    }
    //cerr << need << "\n";
    int BIG = 2 * (1 << need);
    for (int i = 0; i < BIG; ++i) {
        coun1[i] = 0;
        coun2[i] = 0;
    }
    ll S = 0;
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        if (x > need) {
            ll cnt = pows[m - x];
            S += cnt;
            S %= MOD;
            continue;
        }
        int r = ((1 << (x - 1)) - 1 - i) % (1 << x);
        r = (r + (1 << x)) % (1 << x);
        coun1[r + (1 << x)] += 1;
    }
    //for (int i = 0; i < BIG; ++i) {
    //    cerr << coun1[i] << " ";
    //}
    //cerr << "\n";
    int pt = 1;
    for (int i = 2; i < BIG; ++i) {
        if (i == 2 * pt) {
            pt *= 2;
        }
        int r = i - pt;
        for (int j = r; j < BIG / 2; j += pt) {
            coun2[j] += coun1[i];
        }
    }
    //for (int i = 0; i < BIG; ++i) {
    //    cerr << coun2[i] << " ";
    //}
    //cerr << "\n";
    ll mx = 0;
    for (int i = 0; i < (1 << need); ++i) {
        ll cnt = pows[m - need];
        if (i + n >= (1 << need)) {
            cnt--;
        }
        if (m > need || i + n < (1 << need)) {
            mx = max(mx, coun2[i]);
        }
        S += (cnt * coun2[i]) % MOD;
        S %= MOD;
    }
    ll numb = pows[m] - 1 - n + 1;
    numb = (numb % MOD + MOD) % MOD;
    numb *= n;
    numb %= MOD;
    numb = ((numb - S) % MOD + MOD) % MOD;
    for (int i = 0; i < n; ++i) {
        if (a[i] > need) {
            ll r = (-1 - i) % (1 << need);
            r = (r + (1 << need)) % (1 << need);
            mx = max(mx, coun2[r] + 1);
        }
    }
    cout << n - mx << " " << numb << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    precalc();
    while (cin >> n >> m) {
        solve();
    }
}
//*/