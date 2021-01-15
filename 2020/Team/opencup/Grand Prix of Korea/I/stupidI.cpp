#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<vector<int>> g;
vector<int> par;
vector<int> h;

void dfsPar(int v, int p) {
    par[v] = p;
    for (auto i : g[v]) {
        if (i == p) continue;
        h[i] = h[v] + 1;
        dfsPar(i, v);
    }
}

vector<int> a;

void dfsAddSubtree(int v) {
    ++a[v];
    for (auto i : g[v]) {
        if (i == par[v]) continue;
        dfsAddSubtree(i);
    }
}

void addSubtree(int v) {
    //cerr << "addv = " << v << endl;
    dfsAddSubtree(v);
}

void addPath(int, int) {

}

pair<int, int> dfsCalc(int v, int p) {
    int ans = a[v];
    int fans = a[v];
    for (auto i : g[v]) {
        if (i == p) continue;
        auto now = dfsCalc(i, v);
        ans += now.first + now.second;
        fans += now.second;
    }
    return {ans, fans};
}

int calc(int v) {
    return dfsCalc(v, -1).first;
}

int getAns() {
    int ans = 0;
    cerr << "a = " << endl;
    for (auto i : a) {
        cerr << i << " ";
    }
    cerr << endl;
    for (int v = 0; v < n; ++v) {
        int now = calc(v);
        cerr << now << " ";
        if (now < calc(ans) || (now == calc(ans) && h[now] < h[ans])) {
            ans = v;;
        }
    }
    cerr << endl;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n;
    g.assign(n, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    h.assign(n, 0);
    par.assign(n, 0);
    dfsPar(0, -1);
    a.assign(n, 0);
    int q;
    cin >> q;
    while (q--) {
        int t, v;
        cin >> t >> v;
        --v;
        if (t == 1) {
            addSubtree(v);
        } else {
            int u;
            cin >> u;
            --u;
            addPath(u, v);
        }
        int ans = getAns();
        cout << ans + 1 << endl;
    }
    return 0;
}