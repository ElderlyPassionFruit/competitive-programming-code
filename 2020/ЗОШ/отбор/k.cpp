#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		c--;
		g[a].push_back(i + n);
		g[b].push_back(i + n);
		g[c].push_back(i + n);
		g[i + n].push_back(a);
		g[i + n].push_back(b);
		g[i + n].push_back(c);
	}
}

set<int> ans;

int tin[MAXN], up[MAXN], timer = 0;
bool used[MAXN];

void dfs(int v, int p) {
	//cout << "v, p = " << v << " " << p << endl;
	used[v] = true ;
	up[v] = tin[v] = timer++;
	int cnt = 0;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) {
			chkmin(up[v], tin[i]);
		}
		else {
			dfs(i, v);
			chkmin(up[v], up[i]);
			cnt++;
			if (up[i] >= tin[v] && p != -1) {
				//cout << "i, v = " << i << " " << v << endl;
				ans.insert(v); 
			}
		}
	}
	if (p == -1 && cnt > 1)
		ans.insert(v);
}

void run() {
	dfs(0, -1);
	while (!ans.empty() && *ans.begin() < n)
		ans.erase(ans.begin());
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i - n + 1 << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}