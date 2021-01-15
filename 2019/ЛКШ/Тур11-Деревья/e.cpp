#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct vert{
    int v, l, w;
};

const int INF = 1e9 + 10;

namespace fast_operations{
    struct node{
        node *l, *r;
        int key, prior, sz;
        node(){
        }
        node(int new_val) {
            key = new_val;
            prior = (rand() << 16) | rand();
            sz = 1;
            l = nullptr;
            r = nullptr;
        }
        ~node() {
            delete l;
            delete r;
        }
    };

    int sz(node * tree) {
        if (tree == nullptr)
            return 0;
        return tree->sz;
    }

    void upd(node * tree) {
        if (tree == nullptr)
            return;
        tree->sz = sz(tree->l) + sz(tree->r) + 1;
    }

    node * merge(node * tree_l, node * tree_r) {
        if (tree_l == nullptr)
            return tree_r;
        if (tree_r == nullptr)
            return tree_l;
        if (tree_l->prior < tree_r->prior) {
            tree_l->r = merge(tree_l->r, tree_r);
            upd(tree_l);
            return tree_l;
        }
        else {
            tree_r->l = merge(tree_l, tree_r->l);
            upd(tree_r);
            return tree_r;
        }
    }

    pair <node *, node *> split(node * tree, int k) {
        if (tree == nullptr)
            return {nullptr, nullptr};
        if (tree->key > k) {
            auto p = split(tree->l, k);
            tree->l = p.second;
            upd(tree);
            return {p.first, tree};
        }
        else {
            auto p = split(tree->r, k);
            tree->r = p.first;
            upd(tree);
            return {tree, p.second};
        }
    }

    node * insert(node * tree, node * v) {
        if (tree == nullptr)
            return v;
        if (v->prior < tree->prior) {
            auto p = split(tree, v->key);
            v->l = p.first;
            v->r = p.second;
            upd(v);
            return v;
        }
        else {
            if (tree->key >= v->key)
                tree->l = insert(tree->l, v);
            else
                tree->r = insert(tree->r, v);
            upd(tree);
            return tree;
        }
    }

    node * erase(node * tree, int val) {
        if (tree == nullptr)
            return tree;
        if (tree->key == val)
            return merge(tree->l, tree->r);
        else {
            if (tree->key > val)
                tree->l = erase(tree->l, val);
            else
                tree->r = erase(tree->r, val);
            upd(tree);
            return tree;
        }
    }

    int get_ans(node * tree, int k) {
        auto p = split(tree, k);
        int ans = sz(p.first);
        tree = merge(p.first, p.second);
        return ans;
    }

    struct segment_tree{
        vector<node*> tree;
        vector<int> pos;
        vector<vector<int> > help;
        int n;

        segment_tree() {
            n = 0;
            tree = {};
        }   

        void del() {
            for (int i = 0; i < n; i++) {
                delete tree[i];
            }
            help.clear();
            pos.clear();
        }

        void build(int v, int tl, int tr, vector<int> & a) {
            if (tl == tr - 1) {
                tree[v] = new node(a[tl]);
                help[v] = {a[tl]};
                pos[tl] = v;
                return;
            }
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, a);
            build(v * 2 + 1, tm, tr, a);
            help[v].resize(help[v * 2].size() + help[v * 2 + 1].size());
            merge(help[v * 2].begin(), help[v * 2].end(), help[v * 2 + 1].begin(), help[v * 2 + 1].end(), help[v].begin());
            for (auto i : help[v])
                tree[v] = merge(tree[v], new node(i));
        }

        segment_tree(vector<int> a) {
            n = a.size();
            tree.assign(n * 4, 0);
            help.assign(n * 4, {});
            pos.assign(n, 0);
            build(1, 0, n, a);
        }

        int get(int v, int tl, int tr, int l, int r, int k) {
            if (tl >= r || tr <= l)
                return 0;
            if (tl >= l && tr <= r)
                return get_ans(tree[v], k);
            int tm = (tl + tr) / 2;
            return get(v * 2, tl, tm, l, r, k) + get(v * 2 + 1, tm, tr, l, r, k);
        }

        int get(int l, int r, int max_num) {
            return get(1, 0, n, l, r + 1, max_num);
        }

        void add(int p, int val) {
            int v = pos[p];
            while (v) {
                tree[v] = insert(tree[v], new node(val));
                v /= 2;
            }
        }

        void del(int p, int val) {
            int v = pos[p];
            while (v) {
                tree[v] = erase(tree[v], val);
                v /= 2;
            }
        }
    };

    segment_tree tree;
    vector<vert> help;
    map <int, int> pos;
    int mx_pos;
    void make(vector<vert> a) {
        help = a;
        pos.clear();
        mx_pos = 0;

        vector<int> num(help.size());
        for (int i = 0; i < help.size(); i++) {
            num[i] = help[i].w;
            pos[help[i].l] = i;
            chkmax(mx_pos, help[i].l);    
        }
        tree.del();
        tree = segment_tree(num);
        //cerr << "help = " << endl;
        //for (int i = 1; i < tree.tree.size(); i++) {
        //    cerr << "i = " << i << endl;
        //    for (auto j : tree.help[i])
        //        cerr << j << " ";
        //    cerr << endl;
        //}
    }

    int get(int l, int max_num) {
        chkmin(l, mx_pos);
        return tree.get(0, pos[l], max_num);
    }

    void del(int pos) {
        tree.del(pos, help[pos].w);
    }

    void add(int pos) {
        tree.add(pos, help[pos].w);
    }
};


const int MAXN = 1e5 + 10;
int n, maxL, maxW;
vector<pair<int, int> > g[MAXN];

void read() {
    cin >> n >> maxL >> maxW;
    //cerr << n << " " << maxL << " " << maxW << "\n";
    for (int i = 1; i < n; i++) {
        int p, w;
        cin >> p >> w;
        //cerr << p << " " << w << "\n";
        p--;
        g[i].push_back({p, w});
        g[p].push_back({i, w});
    }
    //cout.flush();
}

bool used[MAXN];
int sz[MAXN], centr;

void dfs_centr(int v, int p, int size) {
    sz[v] = 1;
    int m = 0;
    for (auto i : g[v]) {
        if (i.first != p && !used[i.first]) {
            dfs_centr(i.first, v, size);
            sz[v] += sz[i.first];
            chkmax(m, sz[i.first]);
        }
    }
    chkmax(m, size - sz[v]);
    if (m <= size / 2) {
        centr = v;
    }
}

bool operator<(vert a, vert b) {
    return tie(a.l, a.w, a.v) < tie(b.l, b.w, b.v);
}

vector<vert> help;

void dfs_add(int v, int p, int len, int w) {
    help.push_back({v, len, w});
    for (auto i : g[v]) {
        if (!used[i.first] && i.first != p) {
            dfs_add(i.first, v, len + 1, i.second + w);
        }
    }
}

vector<int> fdel;
void dfs_del(int v, int p) {
    fdel.push_back(v);
    for (auto i : g[v]) {
        if (!used[i.first] && i.first != p) {
            dfs_del(i.first, v);
        }
    }
}

long long ans1 = 0;
long long ans2 = 0;

void solve(int v, int size) {
    if (size <= 1) return;
    dfs_centr(v, v, size);
    int u = centr;
    //cerr << "u = " << u << " size = " << size << endl;
    used[u] = true;
    for (auto i : g[u]) {
        if (!used[i.first]) {
            dfs_add(i.first, u, 1, i.second);
        }
    }
    for (auto i : help)
        if (i.l <= maxL && i.w <= maxW)
            ans2++;
    
    sort(help.begin(), help.end());
    
    //cerr << "help = " << endl;
    //for (auto i : help) {
    //    cerr << "v = " << i.v << " l = " << i.l << " w = " << i.w << endl;
    //}

    map <int, int> rhelp;
    for (int i = 0; i < help.size(); i++)
        rhelp[help[i].v] = i;

    //cerr << "rhelp = " << endl;
    //for (auto i : rhelp) {
    //    cerr << i.first << " " << i.second << endl;
    //}

    fast_operations::make(help);

    for (auto i : g[u]) {
        if (!used[i.first]) {
            dfs_del(i.first, u);
            //cerr << "i = " << i.first << endl;
            //cerr << "del = ";
            //for (auto i : fdel) {
            //    cerr << i << " ";
            //}
            //cerr << endl;
            for (auto j : fdel)
                fast_operations::del(rhelp[j]);
            for (auto j : fdel){
                int l = maxL - help[rhelp[j]].l;
                int w = maxW - help[rhelp[j]].w;
                //cerr << "l = " << l << " w = " << w << " get = " << fast_operations::get(l, w) << endl;
                if (l <= 0 || w <= 0) continue;
                ans1 += fast_operations::get(l, w);
            }
            for (auto j : fdel)
                fast_operations::add(rhelp[j]);
            fdel.clear();
        }
    }

    help.clear();

    for (auto i : g[u]) {
        if (!used[i.first]) {
            int fsz = sz[i.first];
            if (fsz > sz[u]) {
                fsz = size - sz[u];
            }
            solve(i.first, fsz);
        }
    }
}


void run() {
    solve(0, n);
}

void write() {
    cout << ans1 / 2 + ans2 << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}