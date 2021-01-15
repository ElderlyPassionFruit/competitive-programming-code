#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Pt{
    int x, y;
};

const int INF = 2e8 + 228;
const int N = 2e5 + 10;
int n, q;
Pt a[N];
Pt compressedA[N];
Pt myQ[N];
int l[N], r[N], m[N];
bool ans[N];

int coordX[2 * N], topX;
int coordY[2 * N], topY;

void compress() {
    topX = 0, topY = 0;
    for (int i = 0; i < n; ++i) {
        coordX[topX++] = a[i].x;
        coordY[topY++] = a[i].y;
    }
    for (int i = 0; i < q; ++i) {
        coordX[topX++] = myQ[i].x;
        coordY[topY++] = myQ[i].y;
    }
    sort(coordX, coordX + topX);
    topX = unique(coordX, coordX + topX) - coordX;
    sort(coordY, coordY + topY);
    topY = unique(coordY, coordY + topY) - coordY;
    for (int i = 0; i < n; ++i) {
        compressedA[i].x = lower_bound(coordX, coordX + topX, a[i].x) - coordX;
        compressedA[i].y = lower_bound(coordY, coordY + topY, a[i].y) - coordY;
    }
}

struct Event{
    int x;
    int type;
    int ly, ry;
    int lx;
    int ind;
    Event() {}
    Event(int _t, int a, int b, int c) {
        type = _t;
        if (type == 1) {
            x = a;
            ly = b;
            ry = c;
        } else if (type == 2) {
            x = a;
            ly = b;
            lx = c;
        } else {
            assert(false);
        }
    }
    Event(int _t, int _x, int _ly, int _ry, int _ind) {
        type = _t;
        x = _x;
        ly = _ly;
        ry = _ry;
        ind = _ind;
    }
};

bool operator<(const Event& a, const Event& b) {
    return tie(a.x, a.type) > tie(b.x, b.type);
}

Event events[2 * N];
int topE;

namespace SegmentTree_tree{
    int n;
    int tree[8 * N], mod[8 * N];

    void init(int _n) {
        n = _n;
        fill(tree, tree + 4 * n, INF);
        fill(mod, mod + 4 * n, INF);
    }

    void push(int v) {
        mod[v * 2] = min(mod[v * 2], mod[v]);
        mod[v * 2 + 1] = min(mod[v * 2 + 1], mod[v]);
        mod[v] = INF;
    }

    int getVal(int v) {
        return min(mod[v], tree[v]);
    }
    
    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] = min(mod[v], val);
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
        tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
    }

    void upd(int l, int r, int val) {
        if (l > r) return;
        upd(1, 0, n, l, r + 1, val);
    }

    void upd(int pos, int val) {
        upd(pos, pos, val);
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return INF;
        if (tl >= l && tr <= r) return getVal(v);
        push(v);
        int tm = (tl + tr) / 2;
        int ans = min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
        return ans;
    }

    int get(int l, int r) {
        if (l > r) return INF;
        return get(1, 0, n, l, r + 1);
    }
};

namespace SegmentTree_pos{
    int n;
    int tree[8 * N], mod[8 * N];

    void init(int _n) {
        n = _n;
        fill(tree, tree + 4 * n, INF);
        fill(mod, mod + 4 * n, INF);
    }

    void push(int v) {
        mod[v * 2] = min(mod[v * 2], mod[v]);
        mod[v * 2 + 1] = min(mod[v * 2 + 1], mod[v]);
        mod[v] = INF;
    }

    int getVal(int v) {
        return min(mod[v], tree[v]);
    }
    
    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] = min(mod[v], val);
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
        tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
    }

    void upd(int l, int r, int val) {
        if (l > r) return;
        upd(1, 0, n, l, r + 1, val);
    }

    void upd(int pos, int val) {
        upd(pos, pos, val);
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return INF;
        if (tl >= l && tr <= r) return getVal(v);
        push(v);
        int tm = (tl + tr) / 2;
        int ans = min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
        return ans;
    }

    int get(int l, int r) {
        if (l > r) return INF;
        return get(1, 0, n, l, r + 1);
    }
};

void relaxEvents(int mxC) {
    sort(events, events + topE);
    //SegmentTree tree(mxC), pos(mxC);
    SegmentTree_tree::init(mxC);
    SegmentTree_pos::init(mxC);

    for (int i = 0; i < topE; ++i) {
        auto event = events[i];
        int type = event.type;
        if (type == 1) {
            SegmentTree_tree::upd(event.ly, event.ry, event.x);
        } else if (type == 2) {
            SegmentTree_pos::upd(event.ly, event.lx);
        } else if (type == 3) {
            int x = event.x;
            int ly = event.ly;
            int ry = event.ry;
            if (ly <= ry) {
                if (SegmentTree_tree::get(ly, ry) - x < m[event.ind]) {
                    ans[event.ind] = false;
                }
            }
            if (ly + 1 <= ry) {
                if (SegmentTree_pos::get(ly + 1, ry) - x < m[event.ind]) {
                    ans[event.ind] = false;
                }
            }
        } else {
            cout << "type = " << type << endl;
            assert(false);
        }
    }
}

void relax() {
    for (int i = 0; i < q; ++i) {
        ans[i] = true;
    }
    topE = 0;
    for (int i = 0; i < q; ++i) {
        int x = myQ[i].x;
        int ly = lower_bound(coordY, coordY + topY, myQ[i].y) - coordY;
        int ry = lower_bound(coordY, coordY + topY, myQ[i].y + m[i]) - coordY;
        --ry;
        events[topE++] = Event(3, x, ly, ry, i);
    }
    for (int i = 0; i < n; ++i) {
        int nxt = i + 1;
        if (nxt == n) nxt = 0;
        if (a[i].x == a[nxt].x) {
            int x = a[i].x;
            int ly = compressedA[i].y;
            int ry = compressedA[nxt].y;
            if (ly > ry) swap(ly, ry);
            assert(ly != ry);
            --ry;
            events[topE++] = Event(1, x, ly, ry);
        } else {
            int x = a[i].x;
            int lx = a[nxt].x;
            if (x < lx) swap(x, lx);
            assert(a[i].y == a[nxt].y);
            int y = compressedA[i].y;
            events[topE++] = Event(2, x, y, lx);
        }
    }
    relaxEvents(topY);

    topE = 0;
    for (int i = 0; i < q; ++i) {
        int x = myQ[i].y;
        int ly = lower_bound(coordX, coordX + topX, myQ[i].x) - coordX;
        int ry = lower_bound(coordX, coordX + topX, myQ[i].x + m[i]) - coordX;
        --ry;
        events[topE++] = Event(3, x, ly, ry, i);
    }
    for (int i = 0; i < n; ++i) {
        int nxt = i + 1;
        if (nxt == n) nxt = 0;
        if (a[i].y == a[nxt].y) {
            int x = a[i].y;
            int ly = compressedA[i].x;
            int ry = compressedA[nxt].x;
            if (ly > ry) swap(ly, ry);
            assert(ly != ry);
            --ry;
            events[topE++] = Event(1, x, ly, ry);
        } else {
            int x = a[i].y;
            int lx = a[nxt].y;
            if (x < lx) swap(x, lx);
            assert(a[i].x == a[nxt].x);
            int y = compressedA[i].x;
            events[topE++] = Event(2, x, y, lx);
        }
    }
    relaxEvents(topX);
}

void solve() {
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    for (int i = 0; i < q; ++i) {
        cin >> myQ[i].x >> myQ[i].y;
        l[i] = 0, r[i] = INF;
    }

    compress();

    while (true) {
        bool need = false;
        for (int i = 0; i < q; ++i) {
            if (l[i] + 1 < r[i]) {
                need = true;
            }
            m[i] = (l[i] + r[i]) / 2;
        }
        if (!need) break;
        relax();
        for (int i = 0; i < q; ++i) {
            if (ans[i]) {
                l[i] = m[i];
            } else {
                r[i] = m[i];
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << l[i] << '\n';
    }
    cerr << "puhh" << endl;
    exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    while (cin >> n >> q) {
        solve();
    }
	return 0;
}