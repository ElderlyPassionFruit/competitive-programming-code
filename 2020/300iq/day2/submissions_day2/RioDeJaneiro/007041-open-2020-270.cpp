#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

mt19937_64 rnd(228);

const int MAGIC = 5;
const int N = 2010;
const int M = 1e6;

ll g[M];

int a[N][N];
ll h[N][N];

ll x[N][N];
ll y[N][N];

int r[N][N], d[N][N];
int bm[N][N], zm[N][N];

ll ok[N][N];
ll ders[N][N];

const ll B = 239;

struct hash_str {
    vector <ll> h, p;
    hash_str(vector <ll> a) {
        int n = (int) a.size();
        if (n == 0) return;
        h.resize(n);
        p.resize(n);
        h[0] = a[0];
        p[0] = 1;
        for (int i = 1; i < n; i++) {
            h[i] = h[i - 1] * B + a[i];
            p[i] = p[i - 1] * B;
        }
    }
    ll get(int l, int r) {
        if (!l) return h[r];
        else return h[r] - h[l - 1] * p[r - l + 1];
    }
};

vector <pair <int, int> > row[N][N];
vector <pair <int, int> > col[N][N];

bitset <N> alive[N];

vector <pair <int, int> > event[N];

pair <int, int> last[M];
int when[N][N];

/*
vector <int> sa(vector <ll> a) {
    map <ll, int> z;
    vector <int> s;
    for (int i = 0; i < (int) a.size(); i++) {
        if (z.count(a[i])) {
            s.push_back(z[a[i]]);
        } else {
            z[a[i]] = sz++;
            s.push_back(z[a[i]]);
        }
    }
    s.push_back(-1);
    int n = (int) s.size();
    vector <int> cl(n);
    for (int i = 0; i < n; i++) {
        cl[i] = s[i];
    }
    vector <int> ord(n);
    for (int i = 0; i < n; i++) {
        ord[i] = i;
    }
    sort(ord.begin(), ord.end(), [&] (int i, int j) {
        return cl[i] < cl[j];
    });
    auto f = [&] (int i, int k) {
        i += k;
        if (i >= n) i -= n;
        return i;
    };
    for (int k = 1; k < n; k *= 2) {
         stable_sort(ord.begin(), ord.end(), [&] (int i, int j) {
            if (cl[i] == cl[j]) {
                return cl[f(i, k)] < cl[f(j, k)];
            } else {
                return cl[i] < cl[j];
            }
        });
        vector <int> ncl(n);
        int sz = 0;
        for (int i = 1; i < n; i++) {
            if (cl[ord[i]] != cl[ord[i - 1]] || cl[f(ord[i], k)] != cl[f(ord[i - 1], k - 1)]) {
                sz++;
            }
            ncl[ord[i]] = sz;
        }
        cl = ncl;
    }
    return ord;
}

vector <int> lcp_arr(vector <int> sa, vector <ll> a) {

}
*/

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    for (int i = 0; i < M; i++) g[i] = rnd();
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 2000, m = 2000;
    cin >> n >> m;
    vector <string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        //for (int j= 0; j < 2 * m; j++) s[i] += 'a';
        for (int j = 0; j < 2 * m; j += 2) {
            a[i][j / 2] = int(s[i][j]) * 256 + int(s[i][j + 1]);
        }
    }
    ll ans = n * m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            h[i][j] = g[a[i][j]];
        }
    }
   for (int i = 0; i < M; i++) last[i] = make_pair(-1, -1);
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            r[i][j] = m;
            if (last[a[i][j]].first == i) {
                r[i][j] = last[a[i][j]].second - j;
            }
            last[a[i][j]] = make_pair(i, j);
        }
    }
    for (int i = 0; i < M; i++) last[i] = make_pair(-1, -1);
    for (int j = 0; j < m; j++) {
        for (int i = n - 1; i >= 0; i--) {
            d[i][j] = n;
            if (last[a[i][j]].second == j) {
                d[i][j] = last[a[i][j]].first - i;
            }
            last[a[i][j]] = make_pair(i, j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = m - 2; j >= 0; j--) {
            r[i][j] = min(r[i][j], r[i][j + 1] + 1);
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            d[i][j] = min(d[i][j], d[i + 1][j] + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            when[i][j] = min(r[i][j], d[i][j]);
        }
    }
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                ok[i][j] = 0;
            }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ok[i + 1][j] = ok[i][j] + h[i][j];
            }
        }
        ll ans = n * m;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j + 1 < m; j++) {
                ders[i][j] = ok[i][j] - ok[i][j + 1];
            }
        }
        vector <hash_str> ok;
        for (int i = 0; i <= n; i++) {
            vector <ll> a;
            for (int j= 0; j < m; j++) {
                a.push_back(ders[i][j]);
            }
            ok.push_back(hash_str(a));
        }

        auto slcp = [&] (int i, int j, int k) {
            int ok = 0;
            int st = j - i;
            int lim = min(m - 1, k + st);
            while (k + 1 <= lim && ders[i][k] == ders[j][k]) k++, ok++;
            return ok;
        };
        auto srev_lcp = [&] (int i, int j, int k) {
            int ok = 0;
            int st = j - i;
            int lim = max(0, k - st);
            while (k - 1 >= lim && ders[i][k - 1] == ders[j][k - 1]) k--, ok++;
            return ok;
        };
         auto lcp = [&] (int i, int j, int k) {
            if (k <= MAGIC) return slcp(i, j, k);
            int lim = j - i;
            int l = 0, r = lim + 1;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (k + mid < (int) ok[i].h.size() && ok[i].get(k, k + mid - 1) == ok[j].get(k, k + mid - 1)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            return l;
        };
        auto rev_lcp = [&] (int i, int j, int k) {
            if (k <= MAGIC) return srev_lcp(i, j, k);
            int lim = j - i;
            int l = 0, r = lim + 1;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (k - mid >= 0 && ok[i].get(k - mid, k - 1) == ok[j].get(k - mid, k - 1)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            return l;
        };
        for (int k = 2; k <= n && k <= m; k++) {
            for (int i = 0; i + k - 1 < n; i++) {
                vector <pair <int, int> > e;
                for (int j = 0; j < m; j += k) {
                    int vr = j + lcp(i, i + k, j);
                    int vl = j - rev_lcp(i, i + k, j);
                    e.push_back({vl, vr});
                }
                vector <pair <int, int> > f;
                for (auto c : e) {
                    if (f.empty() || c.first > f.back().second) {
                        f.push_back(c);
                    } else {
                        f.back().second = c.second;
                    }
                }
                for (auto c : f) {
                    c.second = c.second - k + 1;
                    if (c.first <= c.second) {
                        row[k][i].push_back({c.first, c.second});
                    }
                }
            }
        }
    }
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                ok[i][j] = 0;
            }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ok[i][j + 1] = ok[i][j] + h[i][j];
            }
        }
        ll ans = n * m;
        for (int i = 0; i + 1 < n; i++) {
            for (int j = 0; j <= m; j++) {
                ders[j][i] = ok[i][j] - ok[i + 1][j];
            }
        }
        vector <hash_str> ok;
        for (int i = 0; i <= m; i++) {
            vector <ll> a;
            for (int j= 0; j < n; j++) {
                a.push_back(ders[i][j]);
            }
            ok.push_back(hash_str(a));
        }

        auto slcp = [&] (int i, int j, int k) {
            int ok = 0;
            int st = j - i;
            int lim = min(n - 1, k + st);
            while (k + 1 <= lim && ders[i][k] == ders[j][k]) k++, ok++;
            return ok;
        };
        auto srev_lcp = [&] (int i, int j, int k) {
            int ok = 0;
            int st = j - i;
            int lim = max(0, k - st);
            while (k - 1 >= lim && ders[i][k - 1] == ders[j][k - 1]) k--, ok++;
            return ok;
        };
         auto lcp = [&] (int i, int j, int k) {
            if (k <= MAGIC) return slcp(i, j, k);
            int lim = j - i;
            int l = 0, r = lim + 1;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (k + mid < (int) ok[i].h.size() && ok[i].get(k, k + mid - 1) == ok[j].get(k, k + mid - 1)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            return l;
        };
        auto rev_lcp = [&] (int i, int j, int k) {
            if (k <= MAGIC) return srev_lcp(i, j, k);
            int lim = j - i;
            int l = 0, r = lim + 1;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (k - mid >= 0 && ok[i].get(k - mid, k - 1) == ok[j].get(k - mid, k - 1)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            return l;
        };
        for (int k = 2; k <= n && k <= m; k++) {
            for (int i = 0; i + k - 1 < m; i++) {
                vector <pair <int, int> > e;
                for (int j = 0; j < n; j += k) {
                    int vr = j + lcp(i, i + k, j);
                    int vl = j - rev_lcp(i, i + k, j);
                    e.push_back({vl, vr});
                }
                vector <pair <int, int> > f;
                for (auto c : e) {
                    if (f.empty() || c.first > f.back().second) {
                        f.push_back(c);
                    } else {
                        f.back().second = c.second;
                    }
                }
                for (auto c : f) {
                    c.second = c.second - k + 1;
                    if (c.first <= c.second) {
                        col[k][i].push_back({c.first, c.second});
                    }
                }
            }
        }
    }
    vector <pair <int, int> > ord;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ord.push_back({i, j});
        }
    }
    sort(ord.begin(), ord.end(), [&] (pair <int, int> a, pair <int, int> b) {
        return when[a.first][a.second] > when[b.first][b.second];
    });
    int ptr = -1;
    for (int k = min(n, m); k >= 2; k--) {
        while (ptr + 1 < (int) ord.size() && when[ord[ptr + 1].first][ord[ptr + 1].second] >= k) {
            ptr++;
            alive[ord[ptr].first][ord[ptr].second] = 1;
        }
        for (int i= 0; i <= n; i++) event[i].clear();
        for (int j = 0; j < m; j++) {
            for (auto c : col[k][j]) {
                event[c.first].push_back({j, 1});
                event[c.second + 1].push_back({j, -1});
            }
        }
        bitset <N> cur;
        vector <int> bal(m);
        auto f = [&] (bitset <N> &c, int x) {
            if (x < 0) return 0;
            else {
                return (int) ((c << (N - 1 - x)).count());
            }
        };
        auto add_sum = [&] (bitset <N> &c, int l, int r) {
            return f(c, r) - f(c, l - 1);
        };
        for (int i = 0; i < n; i++) {
            for (auto c : event[i]) {
                bal[c.first] += c.second;
                if (!bal[c.first]) {
                    cur[c.first] = 0;
                } else {
                    cur[c.first] = 1;
                }
            }
            auto t = cur & alive[i];
            for (auto c : row[k][i]) {
                ans += add_sum(t, c.first, c.second);
            }
        }
    }
    cout << ans << endl;
}
