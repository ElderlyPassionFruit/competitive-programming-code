#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int n, m, k;
vector<int> a;

void read() {
	cin >> n >> m >> k;
	a.resize(k);
	for (auto &i : a) {
		cin >> i;
		i--;
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	} 
}

int d_s[MAXN], d_t[MAXN];
queue<int> q;

void build() {
	for (int i = 0; i < n; i++)
		d_s[i] = n + 1;
	d_s[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : g[v]) {
			if (d_s[i] != n + 1) continue;
			d_s[i] = d_s[v] + 1;
			q.push(i);
		}
	}

	for (int i = 0; i < n; i++)
		d_t[i] = n + 1;
	d_t[n - 1] = 0;
	q.push(n - 1);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : g[v]) {
			if (d_t[i] != n + 1) continue;
			d_t[i] = d_t[v] + 1;
			q.push(i);
		}
	}
}

int ans;

void relax(int u, int v) {
	int fans = d_s[n - 1];
	chkmin(fans, 1 + d_s[u] + d_t[v]);
	chkmin(fans, 1 + d_s[v] + d_t[u]);
	chkmax(ans, fans);
}

void solve() {
	/*for (int i = 0; i < n; i++)
		cout << d_s[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << d_t[i] << " ";
	cout << endl;*/

	set<int> used;
	for (auto i : a)
		used.insert(i);
	for (auto i : a) {
		for (auto j : g[i]) {
			if (used.count(j)) {
				cout << d_s[n - 1] << endl;
				exit(0);
			}
		}
	}

	ans = 0;
	sort(all(a), [&] (int i, int j) {return d_s[i] < d_s[j];});
	
	for (int i = 0; i < k; i++) {
		for (int j = i + 1; j < k && j - i <= 1; j++) {
			relax(a[i], a[j]);
		}
	}
}

void run() {
	build();
	solve();
}

void write() {
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