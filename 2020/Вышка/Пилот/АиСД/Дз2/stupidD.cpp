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
    Node() {}
    Node(int _val) {
        L = -1, R = -1, P = -1, val = _val;
    }
};

Node tree[N];

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
}

int ans[N];

void run() {
    for (int i = 0; i < n; ++i) {
        tree[i] = Node(a[i]);
    }
    for (int i = 1; i < n; ++i) {
        add(0, i);
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