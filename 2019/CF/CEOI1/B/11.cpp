#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n, q, w;
set<pair <int, int> > g[MAXN];
vector<pair <int, int> > ed;
vector<int> costs;

void read() {
	cin >> n >> q >> w;
	for (int i = 0; i < n - 1; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].insert({v, cost});
		g[v].insert({u, cost});
		ed.push_back({u, v});
		costs.push_back(cost);
	}
}

void build() {

}

void upd(int ind, int cost) {
	int u = ed[ind].first;
	int v = ed[ind].second;
	
	g[u].erase({v, costs[ind]});	
	g[v].erase({u, costs[ind]});

	costs[ind] = cost;
	
	g[u].insert({v, costs[ind]});
	g[v].insert({u, costs[ind]});	
}

pair <int, int> dfs(int v, int p) {
	pair <int, int> ans = {0, v};
	for (auto i : g[v]) {
		if (i.first != p) {
			auto fans = dfs(i.first, v);
			fans.first += i.second;
			chkmax(ans, fans);
		}
	}
	return ans;
}

int get_ans() {
	auto ans1 = dfs(0, -1);
	auto ans2 = dfs(ans1.second, -1);
	return ans2.first;
}

void wr_g() {
	cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (auto j : g[i]) {
			cout << j.first << " " << j.second << endl;
		}
	}
	cout << endl;
}

vector<int> ans;

void run() {
	build();
	int last = 0;
	for (int test = 0; test < q; test++) {
		int d, e;
		cin >> d >> e;
		d = (d + last) % (n - 1);
		e = (e + last) % w;
		upd(d, e);
		last = get_ans();
		ans.push_back(last);
		//wr_g();
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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