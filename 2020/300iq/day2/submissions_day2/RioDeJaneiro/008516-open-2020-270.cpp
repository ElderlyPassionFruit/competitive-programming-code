#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

mt19937_64 rnd(228);

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

vector <int> ms = {(int)(1e9+7),(int)(1e9+9),(int)(998244353)};
vector <int> bs = {239, 42, 35};

const ll B = 239;

ll hsh[N][N];
ll psh[N][N];

/*
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
*/


vector <pair <int, int> > row[N][N];
vector <pair <int, int> > col[N][N];

bitset <N> alive[N];

vector <pair <int, int> > event[N];

pair <int, int> last[M];
int when[N][N];

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
            r[i][j] = m - j;
            if (last[a[i][j]].first == i) {
                r[i][j] = last[a[i][j]].second - j;
            }
            last[a[i][j]] = make_pair(i, j);
        }
    }
    for (int i = 0; i < M; i++) last[i] = make_pair(-1, -1);
    for (int j = 0; j < m; j++) {
        for (int i = n - 1; i >= 0; i--) {
            d[i][j] = n - i;
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
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (i + 1 < n) when[i][j] = min(when[i][j], when[i + 1][j] + 1);
            if (j + 1 < m) when[i][j] = min(when[i][j], when[i][j + 1] + 1);
            if (i + 1 < n && j + 1 < m) when[i][j] = min(when[i][j], when[i + 1][j + 1] + 1);
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
       for (int i= 0; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                hsh[i][j] = ders[i][j];
                psh[i][j] = 1;
            } else {
                hsh[i][j] = hsh[i][j - 1] * B + ders[i][j];
                psh[i][j] = psh[i][j - 1] * B;
            }
        }
       }
       auto zget = [&] (int i, int l, int r) {
        if (!l) return hsh[i][r];
        else return hsh[i][r] - hsh[i][l - 1] * psh[i][r - l + 1];
       };
         auto lcp = [&] (int i, int j, int k) {
            int lim = j - i;
            int l = 0, r = lim + 1;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (k + mid < n && zget(i, k, k + mid - 1) == zget(j, k, k + mid - 1)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            return l;
        };
        auto rev_lcp = [&] (int i, int j, int k) {
            int lim = j - i;
            int l = 0, r = lim + 1;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (k - mid >= 0 && zget(i, k - mid, k - 1) == zget(j, k - mid, k - 1)) {
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
        for (int j = 0; j + k - 1 < m; j++) {
            for (auto c : col[k][j]) {
                event[c.first].push_back({j, 1});
                event[c.second + 1].push_back({j, -1});
            }
        }
        bitset <N> cur;
        vector <int> bal(m);
        for (int i = 0; i + k - 1  < n; i++) {
            for (auto c : event[i]) {
                bal[c.first] += c.second;
                if (!bal[c.first]) {
                    cur[c.first] = 0;
                } else {
                    cur[c.first] = 1;
                }
            }
            auto t = cur & alive[i];
            ans += t.count();
        }
    }
    cout << ans << endl;
}
