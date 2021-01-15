#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e5 + 10;
int n;
vector<int> g[N];
int sz[N];
int nxt[N];

void dfsSz(int v, int p) {
    sz[v] = 1;
    nxt[v] = -1;
    for (auto i : g[v]) {
        if (i == p) continue;
        dfsSz(i, v);
        sz[v] += sz[i];
        if (nxt[v] == -1 || sz[nxt[v]] < sz[i]) {
            nxt[v] = i; 
        }
    }
}

int ans[N][2];
const int Y = 50;
int coord[Y];

void dfsAns(int v, int p, int x, int y) {
    assert(x >= 1 && x <= 1000000 && y >= 1 && y <= 20);
    ans[v][0] = x, ans[v][1] = y;
    coord[y] = max(coord[y], x);
    if (nxt[v] == -1) return;
    for (auto i : g[v]) {
        if (i == p || i == nxt[v]) continue;
        dfsAns(i, v, coord[y + 1] + 1, y + 1);
    }
    dfsAns(nxt[v], v, x + 1, y);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfsSz(0, 0);
    /*cout << "sz = " << endl;
    for (int i = 0; i < n; i++) {
        cout << sz[i] << " ";
    }
    cout << endl;
    cout << "nxt = " << endl;
    for (int i = 0; i < n; i++) {
        cout << nxt[i] << " ";
    }
    cout << endl;*/
    fill(coord, coord + Y, 0);
    dfsAns(0, 0, 1, 1);

    for (int i = 0; i < n; i++) {
        cout << ans[i][0] << " " << ans[i][1] << "\n";
    }
	return 0;
}