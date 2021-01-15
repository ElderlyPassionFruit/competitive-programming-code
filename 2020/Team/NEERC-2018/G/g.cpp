#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

const int N = 3e4 + 10;
int n, r;
ll k;
ll a[N], b[N], c[N];

mt19937 rnd(time(0));

namespace Treap{
    struct Node{
        int L, R;
        int prior;
        ll val;
        int sz;
        Node() {}
        Node(ll _val) {
            val = _val;
            L = -1, R = -1;
            prior = rnd();
            sz = 1;
        }
    };

    Node tree[N];
    int topTree = 0;

    int getNode(ll val) {
        tree[topTree++] = Node(val);
        return topTree - 1;
    }

    int sz(int root) {
        if (root == -1) return 0;
        return tree[root].sz;
    }

    void upd(int root) {
        if (root == -1) return;
        tree[root].sz = sz(tree[root].L) + sz(tree[root].R) + 1;
    }

    int merge(int L, int R) {
        if (L == -1) return R;
        if (R == -1) return L;
        if (tree[L].prior < tree[R].prior) {
            tree[L].R = merge(tree[L].R, R);
            upd(L);
            return L;
        } else {
            tree[R].L = merge(L, tree[R].L);
            upd(R);
            return R;
        }
    }

    pair<int, int> split(int root, ll val) {
        if (root == -1) return {-1, -1};
        if (tree[root].val > val) {
            auto p = split(tree[root].L, val);
            tree[root].L = p.second;
            upd(root);
            return {p.first, root};
        } else {
            auto p = split(tree[root].R, val);
            tree[root].R = p.first;
            upd(root);
            return {root, p.second};
        }
    }

    int insert(int root, int v) {
        if (root == -1) return v;
        if (v == -1) return root;
        if (tree[v].prior < tree[root].prior) {
            auto p = split(root, tree[v].val);
            tree[v].L = p.first;
            tree[v].R = p.second;
            upd(v);
            return v;
        } else {
            if (tree[root].val > tree[v].val) {
                tree[root].L = insert(tree[root].L, v);
            } else {
                tree[root].R = insert(tree[root].R, v);
            }
            upd(root);
            return root;
        }
    }

    int erase(int root, ll val) {
        if (root == -1) return -1;
        if (tree[root].val == val) {
            return merge(tree[root].L, tree[root].R);
        } else {
            if (tree[root].val > val) {
                tree[root].L = erase(tree[root].L, val);
            } else {
                tree[root].R = erase(tree[root].R, val);
            }
            upd(root);
            return root;
        }
    }

    //multiset<ll> tree;
    ll flag;
    int root;

    void add(ll val) {
        //tree.insert(val - flag);
        int v = getNode(val - flag);
        root = insert(root, v);
    }

    void del(ll val) {
        //tree.erase(tree.find(val - flag));
        root = erase(root, val - flag);
    }

    void addVal(ll val) {
        flag += val;
    }

    int get(ll val) {
        auto p = split(root, val - flag);
        int ans = sz(p.first);
        root = merge(p.first, p.second);
        return ans;
        /*int ans = 0;
        for (auto i : tree) {
            ans += i + flag <= val;
        }
        return ans;*/
    }

    void clear() {
        //tree.clear();
        topTree = 0;
        flag = 0;
        root = -1;
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
        //cerr << "Treap::add = " << cost << endl;
    }
    int ans = 0;
    for (int x = 0; x + r < n; ++x) {
        /*cerr << "puhh" << endl;
        for (auto i : Treap::tree) {
            cerr << i << " ";
        }
        cerr << endl;*/
        ans += Treap::get(sum);
        if (x + r == n - 1) break;
        ll cost = getCost(x, x + r);
        Treap::del(cost);
        //cerr << "cost = " << cost << endl;
        ll fupd = getA(x, x) - getB(x, x) + getC(x + r, x + r) - getB(x + r, x + r);
        //cerr << "fupd = " << fupd << endl;
        Treap::addVal(fupd);
        if (x + 2 * r - 1 < n) {
            ll cost = getCost(x + 1, x + 2 * r - 1);
            Treap::add(cost);
            //cerr << "cost = " << cost << endl;
        }
    }
    return ans;
}

ll calc(ll sum) {
    int notCross = calcNotCross(sum);
    int cross = calcCross(sum);
    //cerr << "notCross = " << notCross << " cross = " << cross << endl;
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