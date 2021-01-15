#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

mt19937_64 rnd(228);

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
        vector <int> need(n);
        for (int i= 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            need[v]++;
            f[v] += h[u];
        }
        vector <pair <ll, ll> > e;
        for (int i = 0; i < n; i++) {
            if (need[i]) {
                e.push_back({f[i], c[i]});
            }
        }
        sort(e.begin(), e.end());
        ll g = 0;
        for (int i = 0; i < (int) e.size(); i++) {
            int j = i;
            while (j < (int) e.size() && e[j].first == e[i].first) j++;
            ll s = 0;
            for (int x = i; x < j; x++) s += e[x].second;
            i = j - 1;
            g = __gcd(g, s);
        }
        cout << g << '\n';
    }
}
