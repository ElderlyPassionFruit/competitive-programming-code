#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1e5 + 10;
int n;
int a[N];

void read() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

struct Node{
    int L, R, P, val;
    int prior;
    Node() {}
    Node(int _val, int _prior) {
        L = -1, R = -1, P = -1, val = _val, prior = _prior;
    }
};

Node tree[N];

/*
void add(int root, int v) {
    if (root == -1) return;
    if (tree[root].val < tree[v].val) {
        if (tree[root].R != -1) {
            add(tree[root].R, v);
        } else {
            tree[root].R = v;
            tree[v].P = root;
        }
    } else {
        if (tree[root].L != -1) {
            add(tree[root].L, v);
        } else {
            tree[root].L = v;
            tree[v].P = root;
        }
    }
}*/

void upd(int v) {
    if (v == -1) return;
    if (tree[v].L != -1) {
        tree[tree[v].L].P = v;
    }
    if (tree[v].R != -1) {
        tree[tree[v].R].P = v;
    }
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

void write(int v) {
    if (v == -1) return;
    write(tree[v].L);
    cout << tree[v].val << " ";
    write(tree[v].R);
}

int ans[N];

void run() {
    for (int i = 0; i < n; ++i) {
        tree[i] = Node(a[i], i);
    }

    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
        return a[x] < a[y];
    });

    /*cout << "ord = " << endl;
    for (auto i : ord) {
        cout << i << " ";
    }
    cout << endl;*/

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        q.push(ord[i]);
    }

    while (q.size() > 1) {
        queue<int> nxtQ;
        while (q.size() > 1) {
            int v = q.front();
            q.pop();
            int u = q.front();
            q.pop();
            nxtQ.push(merge(v, u));
        }
        if (!q.empty()) {
            nxtQ.push(q.front());
        }
        swap(q, nxtQ);
    }
    /*cout << "tree = " << endl;
    write(0);
    cout << endl;
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << tree[i].val << " " << tree[i].prior << " " << tree[i].L << " " << tree[i].R << " " << tree[i].P << endl;
    }
    cout << endl;*/
    for (int i = 1; i < n; ++i) {
        ans[i] = tree[i].P;
    }
}

void write() {
    for (int i = 1; i < n; ++i) {
        cout << a[ans[i]] << " ";
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}