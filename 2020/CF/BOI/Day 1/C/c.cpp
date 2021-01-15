#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int to, ind;
};

const int N = 2e5 + 10, M = 2e5 + 10;
int n, m, q;
vector<edge> g[N];

void read() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
}

bool usedE[N];

void add(int ind) {
	usedE[ind] = true;
}

void del(int ind) {
	usedE[ind] = false;
}

int used[N];
bool ok;

void dfs(int v, int c) {
	used[v] = c;
	for (auto [to, ind] : g[v]) {
		if (usedE[ind]) continue;
		if (!used[to]) {
			dfs(to, 3 - c);
		}
		if (used[v] == used[to]) ok = false;
	}
}

bool check() {
	fill(used, used + n, 0);
	ok = true;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, 1);
		}
	}
	return ok;
}

int maxR[M];

void precalc() {
	fill(maxR, maxR + n, -1);
	if (check()) return;
	for (int i = 0; i < m; i++) {
		int r = i - 1;
		if (i > 0) chkmax(r, maxR[i - 1]);
		while (r + 1 < m) {
			r++;
			add(r);
			if (check()) {
				del(r);
				r--;
				break;
			}
		}
		/*cout << "i = " << i << endl;
		cout << "usedE = " << endl;
		for (int j = 0; j < m; j++) {
			cout << usedE[j] << " ";
		}
		cout << endl;*/
		maxR[i] = r;
		del(i);
	}
}

void run() {
	precalc();
	/*cout << "maxR = " << endl;
	for (int i = 0; i < m; i++) {
		cout << maxR[i] << " ";
	}
	cout << endl;*/
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		if (maxR[l] >= r) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}