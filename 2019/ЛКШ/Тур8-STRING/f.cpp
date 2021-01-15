#include <bits/stdc++.h>

using namespace std;
#define pb push_back

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

namespace hashs{
    const int MOD = 1e9 + 7, b = 179, MAXN = 1e5 + 10;
    int pows[MAXN];

    struct segment_tree{
        vector<int> tree;
        vector<int> sz;
        int n;

        segment_tree() {
            n = 0;
            tree = {};
        }

        pair <int, int> merge(pair <int, int> a, pair <int, int> b) {
            if (a.second == 0) 
                return b;
            if (b.second == 0)
                return a;
            a.first += (long long)b.first * pows[a.second] % MOD;
            a.first %= MOD;
            a.second += b.second;
            return a;
        }

        void build(int v, int tl, int tr, string & s) {
            if (tl == tr - 1) {
                tree[v] = (long long)s[tl] * pows[1] % MOD;
                sz[v] = 1;
                return;
            }
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, s);
            build(v * 2 + 1, tm, tr, s);
            sz[v] = sz[v * 2] + sz[v * 2 + 1];
            tree[v] = merge({tree[v * 2], sz[v * 2]}, {tree[v * 2 + 1], sz[v * 2 + 1]}).first;
        }

        segment_tree(string s) {
            n = s.length();
            tree.assign(n * 4, 0);
            sz.assign(n * 4, 0);
            build(1, 0, n, s);
        }

        pair <int, int> get(int v, int tl, int tr, int l, int r) {
            if (tl >= r || tr <= l)
                return {0, 0};
            if (tl >= l && tr <= r) {
                return {tree[v], sz[v]};
            }
            int tm = (tl + tr) / 2;
            pair <int, int> ans;
            return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        }

        int get(int l, int r) {
            return get(1, 0, n, l, r + 1).first;
        }   

        void upd(int v, int tl, int tr, int l, int r, char x) {
            if (tl >= r || tr <= l)
                return;
            if (tl >= l && tr <= r) {
                tree[v] = (long long) x * pows[1] % MOD;
                return;
            }
            int tm = (tl + tr) / 2;
            upd(v * 2, tl, tm, l, r, x);
            upd(v * 2 + 1, tm, tr, l, r, x);
            tree[v] = merge({tree[v * 2], sz[v * 2]}, {tree[v * 2 + 1], sz[v * 2 + 1]}).first;
        } 

        void upd(int pos, char x) {
            upd(1, 0, n, pos, pos + 1, x);
        }
    };

    segment_tree L, R;
    int n;
    void make(string & s) {
        n = s.size();
        pows[0] = 1;
        for (int i = 1; i < MAXN; i++)
            pows[i] = (long long) pows[i - 1] * b % MOD;
        L = segment_tree(s);
        reverse(s.begin(), s.end());
        R = segment_tree(s);
    }

    bool get(int l, int r) {
        int h1 = L.get(l, r);
        int h2 = R.get(n - 1 - r, n - 1 - l);
        return h1 == h2;
    }

    void upd(int pos, char x) {
        L.upd(pos, x);
        R.upd(n - 1 - pos, x);
    }
} // namespace hashs

void read() {
    string s;
    cin >> s;
    hashs::make(s);
}

vector<bool> ans;

void run() {
    int q;
    cin >> q;
    for (int test = 0; test < q; test++) {
        string type;
        cin >> type;
        if (type == "change") {
            int pos;
            char x;
            cin >> pos >> x;
            pos--;
            hashs::upd(pos, x);
        }
        if (type == "palindrome?") {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            bool fans = hashs::get(l, r);
            ans.push_back(fans); 
        }
    }
}

void write() {
    for (auto i : ans)
        if (i)
            cout << "Yes\n";
        else
            cout << "No\n";
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