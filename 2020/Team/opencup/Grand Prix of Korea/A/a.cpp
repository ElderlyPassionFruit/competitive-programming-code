#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct SegmentTree{
    int n;
    vector<int> mod;
    vector<int> tree;
    SegmentTree() {}
    SegmentTree(int _n) {
        n = _n;
        //tree.assign(n, 0);
        tree.assign(4 * n, 0);
        mod.assign(4 * n, 0);
    }

    void push(int v) {
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        mod[v] = 0;
    }

    int getVal(int v) {
        return tree[v] + mod[v];
    }

    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] += val;
            return;
        }
        int tm = (tl + tr) / 2;
        push(v);
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
        tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
    }

    void upd(int l, int r, int val) {
        /*for (int i = l; i <= r; ++i) {
            tree[i] += val;
        }*/
        upd(1, 0, n, l, r + 1, val);
    }

    int get() {
        //return *min_element(all(tree));
        return getVal(1);
    }

    void wr() {
        cerr << "tree = " << endl;
        for (auto i : tree) {
            cerr << i << " ";
        }
        cerr << endl;
    }
};

const int N = 1e6 + 10;
//const int N = 100;
//const int N = 5;
int n, m, q;

pair<int, int> a[N];
int pos[N];
int b[N];
int cntB[N];

SegmentTree tree;

void build() {
    tree = SegmentTree(N);
    for (int i = 0; i < m; ++i) {
        cntB[b[i]]++;
    }

    /*cerr << "cntB = " << endl;
    for (int i = 0; i < N;++i) {
        cerr << cntB[i] << " ";
    }
    cerr << endl;*/

    for (int i = N - 2; i >= 1; --i) {
        cntB[i] += cntB[i + 1];
    }

    /*cerr << "cntB = " << endl;
    for (int i = 0; i < N; ++i) {
        cerr << cntB[i] << " ";
    }
    cerr << endl;*/

    for (int i = 1; i < N; ++i) {
        tree.upd(i, N - 1, cntB[i]);
    }

    //tree.wr();

    sort(a, a + n);
    reverse(a, a + n);

    /*cerr << "a = " << endl;
    for (int i = 0; i < n; ++i) {
        cerr << a[i].first << " " << a[i].second << endl;
    }*/

    for (int i = 0; i < n; ++i) {
        pos[a[i].second] = i;
    } 

    /*cerr << "pos = " << endl;
    for (int i = 0; i < n; ++i) {
        cerr << pos[i] << " ";
    }
    cerr << endl;*/

    for (int i = 0; i < n; ++i) {
        tree.upd(i + 1, N - 1, -a[i].first);
    }
    //tree.wr();
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

int findL(int x) {
    return lower_bound(a, a + n, make_pair(x, -1), cmp) - a;
}

int findR(int x) {
    return (lower_bound(a, a + n, make_pair(x + 1, -1), cmp) - a) - 1;
}

void Swap(int i, int j) {
    swap(pos[a[i].second], pos[a[j].second]);    
    swap(a[i], a[j]);
}

void addA(int i) {
    //cerr << "a[pos[i]].first = " << a[pos[i]].first << endl;
    int l = findL(a[pos[i]].first);
    a[pos[i]].first++;
    Swap(pos[i], l);
    //cerr << i << " " << l << endl;
    tree.upd(l + 1, N - 1, -1);
    /*cerr << "a = " << endl;
    for (int i = 0; i < n; ++i) {
        cerr << a[i].first << " " << a[i].second << endl;
    }*/
}

void subA(int i) {
    int r = findR(a[pos[i]].first);
    a[pos[i]].first--;
    Swap(pos[i], r);
    tree.upd(r + 1, N - 1, 1);
}

void addB(int i) {
    b[i]++;
    //cntB[b[i]]++;
    tree.upd(b[i], N - 1, 1);
}

void subB(int i) {
    //cntB[b[i]]--;
    tree.upd(b[i], N - 1, -1);
    b[i]--;
}

int getAns() {
    return tree.get() >= 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    build();
    cin >> q;
    while (q--) {
        int t, pos;
        cin >> t >> pos;
        --pos;
        if (t == 1) {
            addA(pos);
        } else if (t == 2) {
            subA(pos);
        } else if (t == 3) {
            addB(pos);
        } else if (t == 4) {
            subB(pos);
        } else {
            assert(false);
        }
        //tree.wr();
        cout << getAns() << '\n';
    }
	return 0;
}