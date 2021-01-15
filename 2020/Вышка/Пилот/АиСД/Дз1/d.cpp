#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

const int N = 5e5 + 10;
int n, l;
ll a[N];

void read() {
    cin >> n >> l;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] = i + (ll) a[i] * l;
    }
}

void init() {
    /*cout << "a = " << endl;
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;*/
    vector<ll> have;
    for (int i = 0; i < n; ++i) {
        have.push_back(a[i]);
    }
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(all(have), a[i]) - have.begin();
    }
    /*cout << "a = " << endl;
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;*/
}

int fenwick[N];

void upd(int pos) {
    for (; pos < n; pos |= pos + 1) {
        ++fenwick[pos];
    }
}

int get(int pos) {
    int ans = 0;
    for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
        ans += fenwick[pos];
    }
    return ans;
}

ll ans;

void run() {
    init();
    ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        //cout << get(a[i] - 1) << endl;
        ans += get(a[i] - 1);
        upd(a[i]);
    }
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}