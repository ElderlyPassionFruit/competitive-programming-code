#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e5 + 10;
int n, m, k;

vector<pair<int, int>> ed;
vector<int> g[N];
queue<int> q;
int dist[N];
int cntAll[N];

void relax(int v, int len) {
    if (dist[v] <= len) return;
    q.push(v);
    dist[v] = len;
}

bool used[N];
vector<int> order;

void dfsOrder(int v) {
    used[v] = true;
    for (auto i : g[v]) {
        if (used[i]) continue;
        dfsOrder(i);
    }
    order.push_back(v);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        ed.push_back({u, v});
        g[v].push_back(u);
        //cntAll[v]++;
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfsOrder(i);
        }
    }
    //reverse(all(order));
    /*cout << "order = " << endl;
    for (auto i : order) {
        cout << i << " ";
    }
    cout << endl;*/
    vector<int> rorder(n);
    for (int i = 0; i < n; ++i) {
        rorder[order[i]] = i;
        g[i].clear();
    }

    for (auto [u, v] : ed) {
        g[rorder[v]].push_back(rorder[u]);
        cntAll[rorder[u]]++;
    }

    fill(dist, dist + n, k + 2);

    for (int i = 0; i < n; ++i) {
        if (cntAll[i]) continue;
        relax(i, 0);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (dist[v] == k + 1) {
            relax(v, 0);
            continue;
        }
        for (auto i : g[v]) {
            relax(i, dist[v] + 1);
        }
    }

    /*cout << "dist = " << endl;
    for (int i = 0; i < n; ++i) {
        cout << dist[i] << " ";
    }
    cout << endl;*/

    if (dist[rorder[0]] == 0) {
        cout << "Denis\n";
    } else {
        cout << "Dasha\n";
    }
	return 0;
}