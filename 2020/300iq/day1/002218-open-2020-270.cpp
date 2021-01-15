#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e5 + 7;

struct val {
    int p, s, cnt, len, best;
};

val mrg(val a, val b) {
    val ret;
    ret.len = a.len + b.len;
    ret.p = (a.len == a.p ? a.p + b.p : a.p);
    ret.s = (b.len == b.s ? a.s + b.s : b.s);
    ret.cnt = a.cnt + b.cnt;
    ret.best = max(a.best, b.best);
    ret.best = max(ret.best, a.s + b.p);
    return ret;
}

val t[4 * N];

void build(int v, int l, int r) {
    if (r - l == 1) {
        t[v] = {0, 0, 0, 1, 0};
    } else {
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m);
        build(v * 2 + 2, m, r);
        t[v] = mrg(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

void upd(int v, int l, int r, int i, int x) {
    if (r - l == 1) {
        if (!x) {
            t[v] = {1, 1, 1, 1, 1};
        } else {
            t[v] = {0, 0, 0, 1, 0};
        }

    } else {
        int m = (l + r) / 2;
        if (i < m) {
            upd(v * 2 + 1, l, m, i, x);
        } else {
            upd(v * 2 + 2, m, r, i, x);
        }
        t[v] = mrg(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

int z;

void smart(vector <int> a) {
    vector <pair <int, int> > st;
    for (int i = 0; i < (int) a.size(); i++) {
        st.push_back({a[i], i});
    }
    sort(st.begin(), st.end());
    int n = (int) st.size();
    build(0, 0, n);
    int mx = 0;
    vector <int> s(n, 0);
    vector <char> term(n, true);
    vector <int> b(n);
    int cur = 0;
    vector <int> mda;
    set <int> q;
    for (int i = 0; i < n; i++) if (term[i]) q.insert(i);
    auto upd_flex = [&] (int i) {
        if (i < 0 || i >= n) return;
        bool nt = (i == 0 || i == n - 1 || s[i] == s[i - 1] || s[i] == s[i + 1]);
                    mda.push_back(i);
        if (nt != term[i]) {
            term[i] = nt;
            upd(0, 0, n, i, term[i]);
            if (term[i]) q.insert(i);
            else q.erase(i);
        }
    };
    auto flex = [&] (int i, int c) {
        s[i] = c;
        upd_flex(i - 1);
        upd_flex(i);
        upd_flex(i + 1);
    };
    vector <int> ans(n, -1);
    set <int> need;
    for (int i = 0; i < n; i++) {
        need.insert(i);
    }
    need.erase(0), need.erase(n - 1);
    ans[0] = a[0], ans[n - 1] = a[n - 1];
    for (int i = 0; i < (int) st.size(); i++) {
        cur = st[i].first;
        flex(st[i].second, 1);
        if (i + 1 == (int) st.size() || st[i].first != st[i + 1].first) {
            mda.push_back(0), mda.push_back(n - 1);
            for (int i : mda) {
                auto it = q.lower_bound(i);
                int r = *it;
                int l = *it;
                if (i != 0) {
                    l = *prev(it);
                }
                int vl = l, vr = r;
                if (s[l] == 1 && s[r] == 1) {
                    vl = l, vr = r;
                } else if (s[l] == 1) {
                    vl = l, vr = l + (r - l) / 2;
                } else if (s[r] == 1) {
                    vr = r, vl = r - (r - l) / 2;
                } else {
                    vl = -1, vr = -1;
                }
                {
                    auto it = need.lower_bound(vl);
                    while (it != need.end() && *it <= vr) {
                        ans[*it] = cur;
                        need.erase(it);
                        it = need.lower_bound(vl);
                    }
                }
            }
            mx = max(mx, t[0].best);
            mda.clear();
        }
    }
    cout << (mx + 1) / 2 << '\n';
    if (z == 1)
        for (int i= 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
    return;
}

mt19937 rnd(228);

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n >> z;
    vector <int> a(n);
    for (int i= 0; i < n; i++) {
        cin >> a[i];
    }
    smart(a);
}
