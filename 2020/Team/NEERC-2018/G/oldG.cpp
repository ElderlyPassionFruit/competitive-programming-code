#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 3e4 + 10;
int n, r;
ll k;
ll
 a[N], b[N], c[N];

namespace Treap{
    multiset<ll> tree;
    void add(ll val) {
        tree.insert(val);
    }

    void del(ll val) {
        tree.erase(tree.find(val));
    }

    void addVal(ll val) {
        multiset<ll> nTree;
        for (auto i : tree) {
            nTree.insert(val + i);
        }
        tree = nTree;
    }

    int get(ll val) {
        int ans = 0;
        for (auto i : tree) {
            ans += i <= val;
        }
        return ans;
    }

    void clear() {
        tree.clear();
    }
};

void buildPrefix() {
    for (int i = 1; i < n; ++i) {
        a[i] += a[i - 1];
        b[i] += b[i - 1];
        c[i] += c[i - 1];
    }
}

ll getA(int l, int r) {
    if (r < l) return 0;
    return a[r] - (l > 0 ? a[l - 1] : 0);
}

ll getB(int l, int r) {
    if (r < l) return 0;
    return b[r] - (l > 0 ? b[l - 1] : 0);
}

ll getC(int l, int r) {
    if (r < l) return 0;
    return c[r] - (l > 0 ? c[l - 1] : 0);
}

ll calcNotCross(ll sum) {
    sum -= getA(0, n - 1);
    ll ans = 0;
    Treap::clear();
    ll cost = getB(n - r, n - 1) - getA(n - r, n - 1);
    Treap::add(cost);
    //cout << "Treap = " << cost << endl;
    //cout << "sum = " << sum << endl;
    for (int x = n - 2 * r; x >= 0; --x) {
        ll myCost = getB(x, x + r - 1) - getA(x, x + r - 1);
        ans += Treap::get(sum - myCost);
        Treap::add(getB(x + r - 1, x + r - 1 + r - 1) - getA(x + r - 1, x + r - 1 + r - 1));
    }
    return ans;
}

ll getCost(int L, int R) {
    //cout << "L = " << L << " R = " << R << endl;
    //cout << getA(0, L - 1) << " " << getB(L, R - r) << " " << getC(R - r + 1, L + r - 1) << " " << getB(L + r, R) << " " << getA(R + 1, n - 1) << endl;
    return getA(0, L - 1) + getB(L, R - r) + getC(R - r + 1, L + r - 1) + getB(L + r, R) + getA(R + 1, n - 1); 
}

ll calcCross(ll sum) {
    if (r == 1) return 0;
    Treap::clear();
    for (int R = r; R < 2 * r - 1 && R < n; ++R) {
        ll cost = getCost(0, R);
        Treap::add(cost);
        cerr << "Treap::add = " << cost << endl;
    }
    int ans = 0;
    for (int x = 0; x + r < n; ++x) {
        cerr << "puhh" << endl;
        for (auto i : Treap::tree) {
            cerr << i << " ";
        }
        cerr << endl;
        ans += Treap::get(sum);
        if (x + r == n - 1) break;
        ll cost = getCost(x, x + r);
        Treap::del(cost);
        cerr << "cost = " << cost << endl;
        ll fupd = getA(x, x) - getB(x, x) + getC(x + r, x + r) - getB(x + r, x + r);
        cerr << "fupd = " << fupd << endl;
        Treap::addVal(fupd);
        if (x + 2 * r - 1 < n) {
            ll cost = getCost(x + 1, x + 2 * r - 1);
            Treap::add(cost);
            cerr << "cost = " << cost << endl;
        }
    }
    return ans;
}

ll calc(ll sum) {
    int notCross = calcNotCross(sum);
    int cross = calcCross(sum);
    cerr << "notCross = " << notCross << " cross = " << cross << endl;
    return notCross + cross;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    cin >> n >> r >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    ll L, R;
    L = 0, R = 0;
    for (int i = 0; i < n; ++i) {
        R += c[i];
    }
    buildPrefix();
    
    //cout << calc(15) << endl;
    //exit(0);
    while (L < R - 1) {
        ll M = (L + R) / 2;
        if (calc(M) < k) {
            L = M;
        } else {
            R = M;
        }
    }
    cout << R << endl;
    return 0;
}