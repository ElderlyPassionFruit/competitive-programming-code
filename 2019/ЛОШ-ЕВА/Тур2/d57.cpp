#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 2*1e5 + 10, MAXLOG = 20;

int n;
char lett[MAXN];
vector<int> g[MAXN];
int ans[MAXN];

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], XOR[MAXN];
int timer = 0;

void dfs_lca(int v, int p, int mask) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];

	mask ^= 1 << (lett[v] - 'a');
	XOR[v] = mask; 

	for (auto i : g[v]) {
		if (i != p) {
			dfs_lca(i, v, mask);
		}
	}

	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (is_upper(v, u))
		return v;
	if (is_upper(u, v))
		return u;
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	}
	return dp[v][0];
}

int get_xor(int v, int u) {
	int l = lca(v, u);
	return XOR[v] ^ XOR[u] ^ (1 << (lett[l] - 'a'));
}


void make_lca() {
	dfs_lca(0, 0, 0);
}

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++)
		cin >> lett[i];
}

int starts[MAXN], finishs[MAXN];
int diff[MAXN];

int dfs_ans(int v, int p) {
	ans[v] = starts[v];
	for (auto i : g[v]) {
		if (i != p) {
			ans[v] += dfs_ans(i, v);
		}
	}
	return ans[v] - finishs[v];
} 

void add(int u, int v) {
	starts[u]++;
	finishs[v]++;
}

void add_path(int i, int j) {
	int l = lca(i, j);
	if (i != l && j != l) {
		add(i, l);
		add(j, l);
		diff[l]++;
		continue;
	}
	if (i != l && j == l) {
		add(i, l);
		continue;
	}
	if (j != l && i == l) {
		add(j, l);
		continue;
	}
}

void run() {
	make_lca();

	unordered_set<int> pows;
	pows.insert(0);
	for (int i = 0; i < 26; i++)
		pows.insert(1 << i);

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int help = get_xor(i, j);
			if (pows.count(help)) {
	//			cout << i << " " << j << " " << help << endl;
				int l = lca(i, j);
				if (i != l && j != l) {
					add(i, l);
					add(j, l);
					diff[l]++;
					continue;
				}
				if (i != l && j == l) {
					add(i, l);
					continue;
				}
				if (j != l && i == l) {
					add(j, l);
					continue;
				}
			}

		}
	}

	/*cout << "starts = ";
	for (int i = 0; i < n; i++) 
		cout << starts[i] << " ";
	cout << endl;
	cout << "finishs = ";
	for (int i = 0; i < n; i++)
		cout << finishs[i] << " ";
	cout << endl; 

	cout << "ans = ";
	for (int i = 0; i < n; i++) 
		cout << ans[i] << " ";
	cout << endl;*/

	dfs_ans(0, 0);
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << ans[i] + 1 - diff[i] << " ";
	}
	cout << endl;
}

signed main() {
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}