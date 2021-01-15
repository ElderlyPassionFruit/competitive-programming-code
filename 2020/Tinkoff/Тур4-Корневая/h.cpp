#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,mmx,avx2,abm")
#pragma GCC optimize("Ofast,O3,inline")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct query{
    int t, l, r, ind;
    query() {}
    query(int a, int b, int c, int d) {
        t = a, l = b, r = c, ind = d;
    }
};

int KT, KL;

bool operator<(const query & a, const query & b) {
    if (a.l / KL != b.t / KL) return a.l / KL < b.l / KL;
    if (a.t / KT != b.t / KT) return a.t / KT < b.t / KT;
    return a.r < b.r;
}

const int MAXN = 2e5 + 10;

struct ft{
    int pos, val, pre_val;
    ft() {}
    ft(int a, int b, int c) {
        pos = a, val = b, pre_val = c;
    }
};

int n, q;
int a[MAXN];
vector<ft> t;
vector<query> Query;

void read() {
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int timer = 0;
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            Query.push_back({timer, l, r, (int)Query.size()});
        } else {
            timer++;
            int pos, val;
            cin >> pos >> val;
            pos--;
            t.push_back({pos, val, a[pos]});
            a[pos] = val;
        }
    }
    KT = max(1.0, pow(timer, 0.63333));
    KL = max(1.0, pow(n, 0.633333));
    for (int i = t.size() - 1; i >= 0; i--) {
        a[t[i].pos] = t[i].pre_val;
    }
}


const int MAXSQRT = 300;


int X[MAXN];

void build() {
    for (int i = 0; i < MAXN; i++)
        X[i] = i / MAXSQRT;

    vector<int> have;
    for (auto i : t)
        have.push_back(i.val);
    for (int i = 0; i < n; i++)
        have.push_back(a[i]);
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());
    for (auto &i : t) {
        i.val = lower_bound(all(have), i.val) - have.begin();
        i.pre_val = lower_bound(all(have), i.pre_val) - have.begin();
    }
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(all(have), a[i]) - have.begin();
    }
}

int cnt[MAXN];
int have[MAXN];

int Cnt[MAXN];

void add_mex(int x) {
      Cnt[X[x]]++;
//    assert(x >= 0 && x < MAXN);
}

void del_mex(int x) {
      Cnt[X[x]]--;
//    assert(x >= 0 && x < MAXN);
}

void add(int x) {
    have[cnt[x]]--;
    if (!have[cnt[x]])
        del_mex(cnt[x]);
    cnt[x]++;
    if (!have[cnt[x]])
        add_mex(cnt[x]);
    have[cnt[x]]++;
}

void del(int x) {
    have[cnt[x]]--;
    if (!have[cnt[x]])
        del_mex(cnt[x]);
    cnt[x]--;
    if (!have[cnt[x]])
        add_mex(cnt[x]);
    have[cnt[x]]++;
}

void add_pos(int pos) {
    add(a[pos]);
}

void del_pos(int pos) {
    del(a[pos]);
}

int l = 0, r = -1, timer = 0;

void add_time(int T) {
    if (T == 0) return;
    T--;
    if (l <= t[T].pos && t[T].pos <= r)
        del_pos(t[T].pos);
    a[t[T].pos] = t[T].val;
    if (l <= t[T].pos && t[T].pos <= r)
        add_pos(t[T].pos);
}

void del_time(int T) {
    if (T == 0) return;
    T--;
    if (l <= t[T].pos && t[T].pos <= r)
        del_pos(t[T].pos);
    a[t[T].pos] = t[T].pre_val;
    if (l <= t[T].pos && t[T].pos <= r)
        add_pos(t[T].pos);
}

int get_ans() {
    /* for (int i = 1; i < MAXN; i++) {
        if (Cnt[i] < MAXSQRT) {
            for (int j = (i - 1) * MAXSQRT + 1; j < MAXN; j++) {
                if (!have[j])
                    return j;
            }
        }
    }
    assert(false);
    return -1;*/
    for (int i = 1; i < MAXN; i++)
        if (!have[i])
            return i;
    return -1;
}

vector<int> ans;

void run() {
    build();
    sort(all(Query));
    ans.resize(Query.size());
    for (auto i : Query) {
        while (l > i.l) {
            l--;
            add_pos(l);
        }
        while (r < i.r) {
            r++;
            add_pos(r);
        }
        while (l < i.l) {
            del_pos(l);
            l++;
        }
        while (r > i.r) {
            del_pos(r);
            r--;
        }
        while (timer > i.t) {
            del_time(timer);
            timer--;
        }
        while (timer < i.t) {
            timer++;
            add_time(timer);
        }
        ans[i.ind] = get_ans();
    }
}

void write() {
    for (auto i : ans)
        cout << i << '\n';
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
