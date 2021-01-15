#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1e6 + 10;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;
const int base = (int)rnd() % 228 + 1337;

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int lp[N];
int p[N];
int topP = 0;

void initPrime() {
    for (int i = 2; i < N; ++i) {
        if (!lp[i]) {
            lp[i] = i;
            p[topP++] = i;
        }
        for (int j = 0; j < topP && p[j] <= lp[i] && i * p[j] < N; ++j) {
            lp[i * p[j]] = p[j];
        }
    }
}

int pows[N];

void build() {
    pows[0] = 1;
    for (int i = 1; i < N; ++i){
        pows[i] = mul(pows[i - 1], base);
    }
    initPrime();
}

struct Node{
    int L, R;
    int prior;
    int h;
    int sz;
    char a;

    Node() {}
    Node(char _a) {
        L = -1, R = -1;
        prior = rnd();
        a = _a;
        h = _a;
        sz = 1;
    }
};

Node tree[N];
int topTree = 0;

int getNode(char a) {
    tree[topTree++] = Node(a);
    return topTree - 1;
}

int sz(int v) {
    if (v == -1) return 0;
    return tree[v].sz;
}

int h(int v) {
    if (v == -1) return 0;
    return tree[v].h;
}

void upd(int v) {
    if (v == -1) return;
    int szL = sz(tree[v].L);
    int szR = sz(tree[v].R);
    tree[v].sz = szL + szR + 1; 
    int hL = h(tree[v].L);
    int hR = h(tree[v].R);
    int val = mul(hL, pows[szR + 1]);
    val = add(val, mul(tree[v].a, pows[szR]));
    val = add(val, hR);
    tree[v].h = val;
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

pair<int, int> split(int v, int size) {
    if (v == -1) return {-1, -1};
    if (size - sz(tree[v].L) - 1 < 0) {
        auto p = split(tree[v].L, size);
        tree[v].L = p.second;
        upd(v);
        return {p.first, v};
    } else {
        auto p = split(tree[v].R, size - sz(tree[v].L) - 1);
        tree[v].R = p.first;
        upd(v);
        return {v, p.second};
    }
}

int insert(int root, int v, int pos) {
    if (root == -1) return v;
    if (v == -1) return root;
    if (tree[v].prior < tree[root].prior) {
        auto p = split(root, pos);
        tree[v].L = p.first;
        tree[v].R = p.second;
        upd(v);
        return v;
    } else {
        if (sz(tree[root].L) >= pos) {
            tree[root].L = insert(tree[root].L, v, pos);
        } else {
            tree[root].R = insert(tree[root].R, v, pos - sz(tree[root].L) - 1);
        }
        upd(root);
        return root;
    }
}

int erase(int root, int pos) {
    if (root == -1) return -1;
    if (sz(tree[root].L) > pos) {
        tree[root].L = erase(tree[root].L, pos);
        upd(root);
        return root;
    } else if (sz(tree[root].L) == pos) {
        return merge(tree[root].L, tree[root].R);
    } else {
        tree[root].R = erase(tree[root].R, pos - sz(tree[root].L) - 1);
        upd(root);
        return root;
    }
}

int hA, hB;

bool check(int &root, int x) {
    auto a = split(root, sz(root) - x);
    hA = h(a.first);
    root = merge(a.first, a.second);
    auto b = split(root, x);
    hB = h(b.second);
    root = merge(b.first, b.second);
    return hA == hB;
}

int n;
string s;
int q;
char t[N];
int ind[N];
char c[N];

void read() {
    cin >> n >> s;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> t[i];
        if (t[i] == '-') {
            cin >> ind[i];
        } else if (t[i] == '+') {
            cin >> ind[i] >> c[i];
        }
    }
}

int ans[N];
int topAns = 0;

int getAns(int& root) {
    int len = sz(root);
    int now = len;
    while (lp[now] > 1) {
        while (len % lp[now] == 0 && check(root, len / lp[now])) {
            len /= lp[now];
        }
        now /= lp[now];
    }
    return len;
}

void run() {
    build();
    int root = -1;
    for (int i = 0; i < n; ++i) {
        int v = getNode(s[i]);
        root = merge(root, v);
    }
    for (int i = 0; i < q; ++i) {
        if (t[i] == '?') {
            ans[topAns++] = getAns(root);
        } else if (t[i] == '+') {
            int v = getNode(c[i]);
            root = insert(root, v, ind[i]);
        } else if (t[i] == '-') {
            root = erase(root, ind[i]);
        } else {
            assert(false);
        }
    }
}

void write() {
    for (int i = 0; i < topAns; ++i) {
        cout << ans[i] << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}