#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
bool used[MAXN];
int tin[MAXN], tout[MAXN];
int timer = 0;

vector<int> g[MAXN];
vector<int> order;
void dfs(int v) {
	used[v] = true;
	tin[v] = timer++;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs(i);
		}
	}
	order.push_back(v);
	tout[v] = timer++;
}

bool is_upper(int a, int b) {
	return tin[b] <= tout[a];
} 

bool cmp(int a, int b) {
	if (is_upper(a, b))
		return true;
	if (is_upper(b, a))
		return false;
	return a < b;
}

int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
	}
}

vector<int> ans;

void run() {
	for (int i = 0; i < n; i++) {
		if (!used[i])
			dfs(i);
	}
	for (int i = 0; i < n; i++) {
		used[i] = false;
	}
	auto x = order;
	reverse(x.begin(), x.end());
	timer = 0;
	for (auto i : x) {
		if (!used[i]) {
			dfs(i);
		}
	}

	cout << "tin = " << endl;
	for (int i = 0; i < n; i++)
		cout << tin[i] << " ";
	cout << endl;
	cout << "tout = " << endl;
	for (int i = 0; i < n; i++)
		cout << tout[i] << " ";
	cout << endl; 

	for (int i = 0; i < n; i++)
		ans.push_back(i);
	sort(ans.begin(), ans.end(), cmp);
}

void write() {
	for (auto i : ans)
		cout << i + 1 << " ";
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