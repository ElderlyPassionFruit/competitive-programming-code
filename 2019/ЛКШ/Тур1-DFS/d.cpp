#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
vector<pair <int, int> > g[MAXN];
int n, m;
int ans[MAXN];
int cnt = 0;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].pb({v, i});
		g[v].pb({u, i});
	}
}	

bool used[MAXN], ed[MAXN];
int root;
int tin[MAXN], up[MAXN], timer = 0;

vector<int> st;
void clear(int num) {
	cnt++;
	while (st.back() != num) {
		ans[st.back()] = cnt;
		st.pop_back();
	}
	if (!st.empty()) {
		ans[st.back()] = cnt;
		st.pop_back();	
	}
}

void add(int num) {
	if (ed[num]) return;
	ed[num] = true;
	st.pb(num);
}

bool have() {
	int ans = 0;
	for (auto i : g[root]) {
		ans += !used[i.first];
	}
	return ans;
}

void dfs(int v) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	int cnt = 0;
	for (auto i : g[v]) {
		if (used[i.first]) {
			add(i.second);
			chkmin(up[v], tin[i.first]);
		}
		else {
			add(i.second);
			cnt++;
			dfs(i.first);
			chkmin(up[v], up[i.first]);
			if (v != root && tin[v] <= up[i.first]) {
				clear(i.second);
			}
			else if (v == root && cnt + have() > 1) {
				clear(i.second);
			}
		}
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			root = i;
			dfs(i);
			if (!st.empty()) {
				clear(st[0]);
			}
		}
	}
}

void write() {
	cout << cnt << endl;
	for (int i = 0; i < m; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
}

signed main() {
	freopen("biconv.in", "r", stdin);
	freopen("biconv.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}