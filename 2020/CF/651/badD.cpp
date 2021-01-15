#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize("O3,Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("avx,avx2,sse")
using namespace std;

int n, k, ans = INT_MAX;
vector<int> kek;
vector<pair<int, int>> tyanki;

bool okay(int cnt, int need, int ost) {
    vector<int> v;
    for (int i = 0; i < cnt; i++) {
        v.push_back(tyanki[i].second);
    }
    sort(v.begin(), v.end());
    int r = 0;
    int lst = INT_MIN;
    for (int e : v) {
        if (lst + 1 != e) {
            r++;
            lst = e;
        }
    }
    if (r < need) {
        return false;
    }
    int gr = tyanki[cnt - 1].first;
    int a = need;
    int b = ost;
    int z = 0;
    for (int i = 0; i < n; i++) {
        if (z == 0) {
            if (kek[i] <= gr) {
                a--;
                z = 1;
            }
        } else {
            b--;
            z = 0;
        }
    }
    if (a <= 0 && b <= 0) {
        return true;
    }
    z = 1;
    a = need;
    b = ost;
    for (int i = 0; i < n; i++) {
        if (z == 0) {
            if (kek[i] <= gr) {
                a--;
                z = 1;
            }
        } else {
            b--;
            z = 0;
        }
    }
    if (a <= 0 && b <= 0) {
        return true;
    }
    return false;
}

int get(int need, int l, int r, int ost) {
    if (l == r) {
        return l;
    } else {
        int m = (l + r) >> 1;
        bool ok = okay(m, need, ost);
        if (ok) {
            return get(need, l, m, ost);
        } else {
            return get(need, m + 1, r, ost);
        }
    }
}

void ask(int a, int b) {
    int need = get(a, 1, n, b);
    int res = tyanki[need - 1].first;
    ans = min(ans, res);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    kek.resize(n);
    tyanki.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> kek[i];
        tyanki[i] = {kek[i], i};
    }
    sort(tyanki.begin(), tyanki.end());
    if (k % 2 == 0) {
        ask(k / 2, k / 2);
    } else {
        int a = k / 2;
        int b = k - a;
        ask(a, b);
        // ask(b, a);
    }
    cout << ans << '\n';

    fflush(stdout);
    return 0;
}
