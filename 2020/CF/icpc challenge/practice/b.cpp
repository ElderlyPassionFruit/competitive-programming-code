#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


mt19937 rnd(time(0));
int n, m;
vector<vector<int>> g;
vector<bool> used;
int now = 0;

void read() {
	cin >> n >> m;
	g.assign(n, {});
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		shuffle(all(g[i]), rnd);
	}
	used.assign(n, 0);
	int type;
	cin >> type;
	if (type == 1) {
		cin >> now;
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			used[i] = x;
		}
	}
}

vector<bool> ansUsed;
int ansNow = 0;

bool add(int x) {
	if (used[x]) return false;
	for (auto i : g[x]) if (used[i]) return false;
	used[x] = true;
	now++;
	if (now > ansNow) {
		ansNow = now;
		ansUsed = used;
	}
	return true;
}

void del(int x) {
	if (!used[x]) return;
	used[x] = false;
	now--;
	int cnt = 0;
	for (auto i : g[x]) {
		cnt += add(i);
	}
	if (!cnt) {
		used[x] = true;
		now++;
	}
}

void run() {
	map<int, int> val;
	for (auto i : g){
		val[i.size()]++;
	}
	for (auto i : val) {
		cerr << i.first << " " << i.second << endl;
	}

	vector<int> order(n);
	iota(all(order), 0);	
	shuffle(all(order), rnd);
	for (int i = 0; i < n; i++) {
		add(i);
	}	
	for (int it = 0; it < 100000; it++) {
		if (it % 10 == 0) {
			cerr << "it = " << it << " ansNow = " << ansNow << " now = " << now << endl;
		}
		vector<int> have;
		for (int i = 0; i < n; i++) {
			if (used[i]) {
				have.push_back(i);
			}
		}
		shuffle(all(have), rnd);
		while (have.size() > 300) {
			have.pop_back();
		}
		for (auto i : have) {
			used[i] = false;
			now--;
		}
		shuffle(all(order), rnd);
		for (int i = 0; i < n; i++) {
			add(order[i]);
			del(order[i]);
		}
	}
}

void write() {
	cout << ansNow << endl;
	for (int i = 0; i < n; i++) {
		cout << ansUsed[i] << " ";
	}
	cout << endl;
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