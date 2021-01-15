#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

mt19937_64 rnd(228);

const int N = 2000;
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

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    for (int i = 0; i < M; i++) g[i] = rnd();
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector <string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < 2 * m; j += 2) {
            a[i][j / 2] = int(s[i][j]) * 256 + int(s[i][j + 1]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            h[i][j] = g[a[i][j]];
        }
    }
    if (n <= 500 && m <= 500) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                r[i][j] = m;
                for (int k = j + 1; k < m; k++) {
                    if (a[i][j] == a[i][k]) {
                        r[i][j] = k - j;
                        break;
                    }
                }
                d[i][j] = n;
                for (int k = i + 1; k < n; k++) {
                    if (a[i][j] == a[k][j]) {
                        d[i][j] = k - i;
                        break;
                    }
                }
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
        ll ans = n * m;
        for (int k = 2; k <= n && k <= m; k++) {
            for (int i = 0; i < n; i++) {
                ll s = 0;
                for (int j = 0; j < k; j++) {
                    s += h[i][j];
                }
                for (int j = 0; j + k - 1< m; j++) {
                    x[i][j] = s;
                    s -= h[i][j];
                    if (j + k < m) s += h[i][j + k];
                }
            }

            for (int j = 0; j < m; j++) {
                ll s = 0;
                for (int i = 0; i < k; i++) {
                    s += h[i][j];
                }
                for (int i = 0; i + k - 1 < n; i++) {
                    y[i][j] = s;
                    s -= h[i][j];
                    if (i + k < n) s += h[i + k][j];
                }
            }
            for (int i = n - 1; i >= 0; i--) {
                for (int j = 0; j < m; j++) {
                    if (i + 1 < n && x[i][j] == x[i + 1][j]) {
                        bm[i][j] = 1 + bm[i + 1][j];
                    } else {
                        bm[i][j] = 1;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = m - 1; j >= 0; j--) {
                    if (j + 1 < m && y[i][j] == y[i][j + 1]) {
                        zm[i][j] = 1 + zm[i][j + 1];
                    } else {
                        zm[i][j] = 1;
                    }
                }
            }
            for (int i = 0; i + k - 1 < n; i++) {
                for (int j = 0; j + k - 1 < m; j++) {
                    if (r[i][j] >= k && d[i][j] >= k && bm[i][j] >= k) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << endl;
    }
}
