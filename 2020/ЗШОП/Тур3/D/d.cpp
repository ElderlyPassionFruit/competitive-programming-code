#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
#define int ll
 
const ll INF = 1e17;

struct edge{
    int u, v, cost, d;
    edge() {}
};
 
vector<edge> ed;
int n, m;
 
void read() {
    cin >> n >> m;
    ed.resize(m);
    for (auto &i : ed) {
        cin >> i.u >> i.v >> i.cost >> i.d;
        i.u--;
        i.v--;
    }
}
 
const int MAXN = 210;
vector<int> g[MAXN], gr[MAXN];
   
ll ans = INF;
 
vector<int> order;
vector<bool> used;

void dfs_order(int v) {
	used[v] = true;
	for (auto i : g[v])
		if (!used[i])
			dfs_order(i);
	order.push_back(v);
}

vector<int> color;

void dfs_color(int v, int c) {
	color[v] = c;
	for (auto i : gr[v]) {
		if (color[i] == -1) {
			dfs_color(i, c);
		}
	}
}

vector<int> ng[MAXN];
vector<bool> goodS, goodT;

void dfs_goodS(int v, int t) {
	goodS[v] = true;
	if (v == t) return;
	for (auto i : ng[v]) {
		if (!goodS[i]) {
			dfs_goodS(i, t);
		}
	}
}

void dfs_goodT(int v, int s) {
	goodT[v] = true;
	if (s == v) return;
	for (auto i : ng[v]) {
		if (!goodT[i]) {
			dfs_goodT(i, s);
		}
	}
}

bool dfs_check(int v, int need) {
	if (v == need) return true;
	used[v] = true;
	for (auto i : ng[v]) {
		if (!used[i]) {
			if (dfs_check(i, need))
				return true;
		}
	}
	return false;
}

int c = 0;

void build_norm() {
	for (int i = 0; i < c; i++)
  		ng[i].clear();

	for (auto i : ed) {
  		int u = color[i.u];
  		int v = color[i.v];
  		if (u == v) continue;
  		ng[u].push_back(v);
  	}

  	for (int i = 0; i < c; i++) {
  		sort(all(ng[i]));
  		ng[i].resize(unique(all(ng[i])) - ng[i].begin());
  	}
}

void build_rev() {
	for (int i = 0; i < c; i++)
  		ng[i].clear();

	for (auto i : ed) {
  		int u = color[i.u];
  		int v = color[i.v];
  		if (u == v) continue;
  		ng[v].push_back(u);
  	}

  	for (int i = 0; i < c; i++) {
  		sort(all(ng[i]));
  		ng[i].resize(unique(all(ng[i])) - ng[i].begin());
  	}
}

ll solve(int s, int t) {
	s = color[s];
	t = color[t];

	build_norm();

  	used.assign(c, 0);
	if (!dfs_check(t, s)) return INF;

  	goodS.assign(c, 0);
  	dfs_goodS(color[s], -1);

  	build_rev();
  	goodT.assign(c, 0);
  	dfs_goodT(color[t], -1);

  	cout << "s = " << s << " t = " << t << endl;    
  	cout << "goodS = " << endl;
  	for (auto i : goodS)
  		cout << i << " ";
  	cout << endl;

  	cout << "goodT = " << endl;
  	for (auto i : goodT)
  		cout << i << " ";
  	cout << endl;
	
    cout << "color = " << endl;
    for (auto i : color)
    	cout << i << " ";
    cout << endl;
    

  	ll ans = INF;

    vector<edge> have;
    for (auto i : ed) {
    	//if (color[i.u] == color[i.v]) continue;
    	int u = color[i.u];
    	int v = color[i.v];
    	if (u == v) continue;
    	//if (s == color[0]) swap(u, v);
    	if (goodS[v] && goodT[u]) {
    		have.push_back(i);
    		//chkmin(ans, i.d);
    	}
    }

    if (have.size() >= 2) {
    	for (auto i : have) {
    		chkmin(ans, i.d);
    	}
    }

    return ans;
}

void run() {
    for (auto i : ed) {
        g[i.u].push_back(i.v);
        gr[i.v].push_back(i.u);
    }   
    used.assign(n, 0);
    for (int i = 0; i < n; i++)
    	if (!used[i])
    		dfs_order(i);

    reverse(all(order));
    color.assign(n, -1);
    used.assign(n, 0);

    for (auto i : order){
    	if (color[i] == -1)
    		dfs_color(i, c++);
    }

    if (color[0] == color[n - 1]) {
    	ans = 0;
    	return;
    }
    chkmin(ans, solve(0, n - 1));
    chkmin(ans, solve(n - 1, 0));
}
 
void write() {
    if (ans == INF) ans = -1;
    cout << ans << endl;
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

/*
4 4
3 1 0 2
3 2 0 1
3 4 0 1
1 4 0 2

3 2
3 1 0 1
1 2 0 1
*/