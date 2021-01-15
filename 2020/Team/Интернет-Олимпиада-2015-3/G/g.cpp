#include <bits/stdc++.h>

using namespace std;
#define pb push_back

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXLEN = 21;

namespace binary_bor{
    struct node{
        node * l, * r;

        node() {
            l = nullptr;
            r = nullptr;
        }

        ~node() {
            if (l != nullptr)
                delete l;
            if (r != nullptr)
                delete r;
        }
    };

    node * add(node * tree, int x, int len) {
        if (!len)
            return tree;
        if ((x >> (len - 1)) & 1) {
            if (tree->r == nullptr)
                tree->r = new node();
            tree->r = add(tree->r, x, len - 1);
        }
        else {
            if (tree->l == nullptr)
                tree->l = new node();
            tree->l = add(tree->l, x, len - 1);
        }
        return tree;
    }

    int get(node * tree, int need, int len) {
        if (!len)
            return 0;
        bool flag = (need >> (len - 1)) & 1;
        if ((!flag && tree->l != nullptr) || (flag && tree->r == nullptr)) {
            return get(tree->l, need, len - 1);
        }
        else {
            return get(tree->r, need, len - 1) + (1 << (len - 1));
        }
    }

    node * build(vector<int> a) {
        node * tree = new node();
        for (auto i : a) {
            tree = add(tree, i, MAXLEN);
        }
        return tree;
    }


} // namespace binary_bor

int n;
vector<int> a;
void read() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

long long solve(int l, int r) {
    if (l == r - 1) {
        return (long long)a[l] * a[l];
    }

    int m;
    m = (l + r) / 2;

    long long ans = 0;

    vector<int> suff, suff_max;
    suff.push_back(a[m - 1]);
    suff_max.push_back(a[m - 1]);
    for (int i = m - 2; i >= l; i--) {
        suff.push_back(a[i] ^ suff.back());
        suff_max.push_back(max(a[i], suff_max.back()));
    }
    
    vector<int> pref, pref_max;
    pref.push_back(a[m]);
    pref_max.push_back(a[m]);
    for (int i = m + 1; i < r; i++) { 
        pref.push_back(a[i] ^ pref.back());
        pref_max.push_back(max(a[i], pref_max.back()));
    }   

    binary_bor::node * tree_suff = binary_bor::build(suff);
    for (int i = 0; i < r - m; i++) {
        int need = (~pref[i]) & ((1 << MAXLEN) - 1);
        long long have = binary_bor::get(tree_suff, need, MAXLEN);
        have ^= pref[i];
        have *= (long long)pref_max[i];
        chkmax(ans, have);
    }

    delete tree_suff;

    binary_bor::node * tree_pref = binary_bor::build(pref);
    for (int i = 0; i < m - l; i++) {
        int need = (~suff[i]) & ((1 << MAXLEN) - 1);
        long long have = binary_bor::get(tree_pref, need, MAXLEN);
        have ^= suff[i];
        have *= (long long)suff_max[i];
        chkmax(ans, have);
    }

    delete tree_pref;

    chkmax(ans, solve(l, m));
    chkmax(ans, solve(m, r));
    return ans;
}

long long ans;

void run() {
    ans = solve(0, n);
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("maxxor.in", "r", stdin);
    freopen("maxxor.out", "w", stdout);
    read();
    run();
    write();
    return 0;
}