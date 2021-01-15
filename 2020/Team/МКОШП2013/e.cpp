#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

const int MAXN = 2e5 + 10;
set <int> g[MAXN];

struct event{
	int p, ind;
	event() {}
	event(int a, int b) {
		p = a, ind = b;
	}
};

bool operator<(event a, event b) {
	return tie(a.p, a.ind) < tie(b.p, b.ind);
}

set<event> q;

int n, m;

void build() {
	for (int i = 0; i < n; i++) {
		q.insert({(int)g[i].size(), i});
	}
}

void no() {
	cout << "NO" << endl;
	exit(0);
}

set<int> used;

void dfs(int v) {
	used.insert(v);
	for (auto i : g[v]) {
		if (!used.count(i)) {
			dfs(i);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].insert(v);
		g[v].insert(u);
	}

	build();
	set<int> cycle;
	while (!q.empty() && q.begin()->p == 1) {
		auto x = *q.begin();
		q.erase(q.begin());
		int v = *g[x.ind].begin();
		g[x.ind].erase(g[x.ind].begin());
		
		if (g[v].size() != 2 && g[v].size() != 4) no();
		if (g[v].size() == 2) {
			q.erase({(int)g[v].size(), v});
			g[v].erase(x.ind);
			q.insert({(int)g[v].size(), v});
			continue;
		}
		else {
			if (cycle.count(v)) no();
			cycle.insert(v);
			q.erase({(int)g[v].size(), v});
			g[v].erase(x.ind);
			q.insert({(int)g[v].size(), v});
		}
	}

	int cnt_2 = 0, cnt_3 = 0, cnt_other = 0, x = -1;
	for (auto i : q) {
		if (i.p == 2) {
			cnt_2++;
		}
		else if (i.p == 3) {
			cnt_3++;
		}
		else {
			cnt_other++;
			x = i.ind;
		}
	}

	//cout << "2 = " << cnt_2 << " 3 = " << cnt_3 << " cnt_other = " << cnt_other << " x = " << x << endl;
	if (cnt_other == 0 && cnt_3 != 0) {
		x = -1;
		for (auto i : q) {
			if (i.p == 3 && !cycle.count(i.ind)) {
				if (x == -1) {
					x = i.ind;
					cnt_3--;
					cnt_other++;
				}
				else {
					no();
				}
			}
		}
		if (x == -1)
			no();
	}



	if (cnt_other > 1) no();
	if (cnt_other == 0) {
		if (cnt_2 != 0 && cnt_3 == 0) {
			dfs(q.begin()->ind);
			for (auto i : used) {
				if (!cycle.count(i)) {
					used.erase(i);
					break;
				}
			}
			if (cycle == used) {
				cout << "YES" << endl;
				return 0;
			}
		}
		no(); 
	}
	if(g[x].size() != cnt_3) no();

	for (auto i : g[x]) {
		q.erase({(int)g[i].size(), i});
		g[i].erase(x);
		q.insert({(int)g[i].size(), i});
	}

	q.erase({(int)g[x].size(), x});

	/*cout << "q = " << endl;
	for (auto i : q)
		cout << i.p << " " << i.ind << endl;
	*/
	while (!q.empty() && q.begin()->p == 1) {
		auto x = *q.begin();
		q.erase(q.begin());
		int v = *g[x.ind].begin();
		g[x.ind].erase(v);
		
		q.erase({(int)g[v].size(), v});
		g[v].erase(x.ind);
		q.insert({(int)g[v].size(), v});
	}


	for (auto i : q) {
		if (i.p != 2){
			//cout << "sosal" << endl;
			no();
		}
	}

	//cout << "x = " << x << endl;

	dfs(q.begin()->ind);
	if (used != cycle) no();

	cout << "YES" << endl;
	return 0;
}





















