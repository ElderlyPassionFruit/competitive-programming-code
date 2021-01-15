#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int g[MAXN][2];
int num[MAXN];
int n;
int start;
void read() {
	cin >> n;
	set<int> root;
	for (int i = 0; i < n; i++)
		root.insert(i);
	for (int i = 0; i < n; i++) {
		cin >> num[i] >> g[i][0] >> g[i][1];
		if (g[i][0] > 0) {
			g[i][0]--;	
			root.erase(g[i][0]);	
		}
		if (g[i][1] > 0) {
			g[i][1]--;
			root.erase(g[i][1]);
		}
	}
	assert(root.size() == 1);
	start = *root.begin();
}

multiset<int> used;
set<int> have;

void dfs(int v, int l, int r) {
	if (v == -1)
		return;
	if (num[v] >= l && num[v] <= r)
		have.insert(num[v]);

	dfs(g[v][0], l, min(num[v] - 1, r));
	dfs(g[v][1], max(num[v] + 1, l), r);
}

int ans;
void run() {
	dfs(start, 0, 1e9);
	ans = 0;
	for (int i = 0; i < n; i++) {
		if (have.find(num[i]) == have.end())
			ans++;
	}
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