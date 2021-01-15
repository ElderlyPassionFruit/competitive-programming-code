#include <bits/stdc++.h>

using namespace std;
#define int long long
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXK = 15;
int k, n;
vector<int> a[MAXK];
int Sum[MAXK];

map<int, int> pos;
void read() {
	cin >> k;
	for (int i = 0; i < k; i++) {
		int n;
		cin >> n;
		a[i].resize(n);
		Sum[i] = 0;
		for (auto &j : a[i]){
			cin >> j;
			pos[j] = i;
			Sum[i] += j;
		}
		sort(all(a[i]));
	}
}

void no() {
	cout << "No" << endl;
	exit(0);
}

const int INF = -1;

int sum = 0;	
vector<pair<int, int>> ans;
int g[MAXK][MAXK];
int last_bit[1 << MAXK];

void build() {
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++) 
			g[i][j] = INF;
	for (int i = 0; i < k; i++) {
		last_bit[1 << i] = i;
	}
	for (int i = 0; i < k; i++) {
		for (auto j : a[i]) {
			int x = sum - (Sum[i] - j);
			if (!pos.count(x)) continue;
			int p = pos[x];
			if (p == i) continue;
			g[p][i] = x;
		}
	}
}

bool dp[1 << MAXK][MAXK];
int check[1 << MAXK];
int par[1 << MAXK][MAXK];

void calc1() {
	for (int mask = 0; mask < (1 << k); mask++) {
		int v = last_bit[(mask & (-mask))];
		if ((1 << v) == mask) {
			dp[mask][v] = true;
			par[mask][v] = v;
			continue;
		}
		for (int u = 0; u < k; u++) {
			if (!((mask >> u) & 1)) continue;
			if (v == u) continue;
			if ((mask ^ (1 << v) ^ (1 << u)) == 0) {
				dp[mask][u] = true;
				par[mask][u] = v;
				continue;
			}
			for (int x = 0; x < k; x++) {
				if (x == v) continue;
				if (x == u) continue;
				if (!((mask >> x) & 1)) continue;
				if (g[x][u] == INF) continue;
				if (!dp[mask ^ (1 << u)][x]) continue;
				dp[mask][u] = true;
				par[mask][u] = x;
				break;
			}
		}
	}
	for (int mask = 1; mask < (1 << k); mask++) {
		check[mask] = -1;
		int v = last_bit[(mask & (-mask))];
		if ((1 << v) == mask) {
			if (Sum[v] == sum) {
				check[mask] = v;
				continue;
			}
		}
		for (int u = 0; u < k; u++) {
			if (!dp[mask][u]) continue;
			if (g[u][v] == INF) continue;
			check[mask] = u;
			break;
		}
	}
	cout << "check = " << endl;
	for (int i = 0; i < (1 << k); i++) {
		cout << i << " " << check[i] << endl;
	}
	cout << endl;
	exit(0);
}

bool dp2[1 << MAXK];
int par2[1 << MAXK];

void calc2() {
	dp2[0] = 1;
	for (int mask = 1; mask < (1 << k); mask++) {
		int s = mask;
		while (s > 0) {
			if (dp2[mask ^ s] && check[s] != -1) {
				dp2[mask] = true;
				par2[mask] = s;
				break;
			}
			s = ((s - 1) & mask);
		}
	}
}

void make_path(int mask) {
	int v = last_bit[(mask & (-mask))];
	if ((1 << v) == mask) {
		ans[v] = {a[v][0], v};
		return;
	}
	int u = check[mask];
	ans[u] = {g[u][v], v};
	while (u != v) {
		ans[par[mask][u]] = {g[par[mask][u]][u], u};
		u = par[mask][u];
	}
}

void make_ans() {
	ans.resize(k);
	int mask = (1 << k) - 1;
 	if (!dp2[mask]) no();
 	while (mask) {
 		make_path(par2[mask]);
 		mask ^= par2[mask];
 	}
}

void run() {
	for (int i = 0; i < k; i++) {
		for (auto j : a[i]) {
			sum += j;
		}
	}
	cout << sum << endl;
	if (sum % k != 0) no();
	sum /= k;

	cout << sum << endl;

	cout << "Sum = " << endl;
	for (int i = 0; i < k; i++)
		cout << Sum[i] << " ";
	cout << endl;

	build();
	cout << "g = " << endl;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cout << g[i][j] << " "; 
		}
		cout << endl;
	}
	calc1();
	calc2();
	make_ans();
}

void write() {
	cout << "Yes" << endl;
	for (auto i : ans)
		cout << i.first << " " << i.second + 1 << endl;
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