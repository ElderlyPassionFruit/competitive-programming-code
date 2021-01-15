#pragma GCC target("sse,sse2,sse3,sse4,ssse3,sse4.1,sse4.2,avx,avx2,tune=native,mmx,popcnt")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
 
const int MAXN = 1e3 + 10;
char table[MAXN][MAXN];
int n, m;
 
void read() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            cin >> table[i][j]; 
}
 
struct segment{
    int l, r;
    segment() {}
    segment(int a, int b) {
        l = a, r = b;
    }
};
 
void rebuild(vector<segment> & a) {
    if (a.empty()) return;
    vector<segment> ans;
    ans.push_back(a[0]);
    for (int i = 1; i < a.size(); i++) {
        if (ans.back().r >= a[i].l - 1)
            ans[ans.size() - 1].r = a[i].r;
        else
            ans.push_back(a[i]);
    }
    a = ans;
}
 
vector<segment> have[MAXN * 2];
 
void build() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (table[j][i] == '.') continue;
            have[i].push_back({j, j});
        }
    }
}
 
const int INF = 1e6;
 
int tree[MAXN * 8];
int mod[MAXN * 8];
 
int N;
 
void push(int v) {
    mod[v * 2] += mod[v];
    mod[v * 2 + 1] += mod[v];
    mod[v] = 0;
}
 
int get_val(int v) {
    return tree[v] + mod[v];
}
 
int get() {
    return get_val(1);
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
    tree[v] = min(get_val(v * 2), get_val(v * 2 + 1));
}
 
void upd(int l, int r, int val) {
    upd(1, 0, N, l, r + 1, val);
}
 
void clear_all() {
    for (int i = 0; i < MAXN * 8; i++) {
        tree[i] = 0;
        mod[i] = 0;
    }
}
 
bool check(int h, int w) {
    if (h < n || w < m) return false;
    N = h;
    //clear_all();
    bool ans = true;
    for (int i = 0; i < w; i++) {
        for (auto j : have[i]) {
            upd(j.l, j.r, 1);
        }
        int pos = i - (w - m + 1);
        if (pos >= 0) {
            for (auto j : have[pos]) {
                upd(j.l, j.r, -1);
            }
        }
        if (get() == 0) ans = false;
    }
    int pos = m - 1;
    for (auto j : have[pos]) {
        upd(j.l, j.r, -1);
    }
    return ans;
}
 
int pos;
 
int get(int h) {
    if (!check(h, pos)) return INF;
    while (check(h, pos - 100))
    	pos -= 100; 
    while (check(h, pos - 10))
    	pos -= 10;
    while (check(h, pos - 1))
        pos--;
    return pos;
}
 
void add() {
    for (int i = 0; i < m; i++) {
        for (auto &j : have[i])
            j.r++;
    }
}
 
void rebuild() {
    add();
    for (int i = 0; i < m; i++)
        rebuild(have[i]);
}
 
int h, w;
 
void run() {
    build();
    h = 2 * n;
    w = 2 * m;
    pos = 2 * m;
    //rebuild();
    //rebuild();
    //cout << get(7);
    //cout << endl;
    //exit(0);
    for (int i = n; i <= 2 * n; i++) {
        int j = get(i);
        if (h * w > i * j) {
            h = i, w = j;
        }
        rebuild();
    }
}
 
void write() {
    cout << h << " " << w << endl;
}
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    read();
    run();
    write();
    return 0;
}
 
 
/*
5 6
X...XX
XX...X
......
..XX..
XXX..X
 
 
*/