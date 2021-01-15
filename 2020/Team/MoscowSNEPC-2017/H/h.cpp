#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

ll sum(ll l, ll r) {
    if (l > r) {
        return 0;
    }
    if (l < 0) {
        l = 0;
    }
    if (r < 0) {
        r = 0;
    }
    int ansL = l + r;
    int ansR = r - l + 1;
    if (ansL & 1) ansR >>= 1;
    else ansL >>= 1;
    
    return ansL * ansR;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);

    ll T;
    int n, m;
    cin >> T >> n >> m;
    int la = 1, lb = 1;
    bool st = 1;
    ll mnt = 0, mxt = 0;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (st) {
            mnt += sum(b - a + 1, b);
            mxt += sum(b, b + a - 1);
            st = 0;
        } else {
            if (abs(lb - b) > abs(la - a)) {
                cout << "No";
                return 0;
            } else {
                ll d = abs(la - a) - abs(lb - b);
                int mnb = min(b, lb), mxb = max(b, lb);
                mnt += sum(mnb, mxb) + sum(mnb - (d + 1) / 2 + 1, mnb) + sum(mnb - d / 2, mnb - 1);
                mxt += sum(mnb, mxb) + sum(mxb, mxb + (d + 1) / 2 - 1) + sum(mxb + 1, mxb + d / 2);
            }
        }
        la = a;
        lb = b;
        mnt -= lb;
        mxt -= lb;
    }
    mnt += sum(lb - (n - la), lb);
    mxt += sum(lb, lb + (n - la));
    if (mnt <= T && mxt >= T) {
        cout << "Yes";
    } else {
        cout << "No";
    }
	return 0;
}

/*
1 2 2
2 0
2 1
*/