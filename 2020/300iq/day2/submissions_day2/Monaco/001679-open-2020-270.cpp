#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

mt19937_64 rnd(228);

const int N = 5e5 + 7;

ll h[N];

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector <ll> h(n);
        vector <ll> f(n);
        for (int i= 0; i < n; i++) h[i] = rnd();
        vector <ll> c(n);
        for (int i = 0; i < n; i++) cin >> c[i];
        for (int i= 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            f[v] += h[u];
        }
        map <ll, ll> s;
        for (int i = 0; i < n; i++) {
            s[f[i]] += c[i];
        }
        ll g = 0;
        for (auto c : s) {
            g = __gcd(g, c.second);
        }
        cout << g << '\n';
    }
}
