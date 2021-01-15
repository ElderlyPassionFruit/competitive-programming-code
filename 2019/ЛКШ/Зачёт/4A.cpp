#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;

vector<int> g[MAXN];
vector<int> gr[MAXN];

int n;
int col[MAXN];
int pos[MAXN];
int rpos[MAXN][2];
bool type[MAXN];


void read() {
	for (int i = 0; i < MAXN; i++)
		rpos[i][0] = -1;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> col[i];
	for (int i = 0; i < 2 * n; i++) {
		cin >> pos[i];
		pos[i]--;
		if (rpos[pos[i]][0] == -1)
			rpos[pos[i]][0] = i;
		else
			rpos[pos[i]][1] = i;
	}
}

void relax(int pos1, int pos2) {
	int c1 = col[pos[pos1]];
	int c2 = col[pos[pos2]];
	if (c1 != c2) return;
	int i = pos[pos1];
	int j = pos[pos2];
	if (i == j) return;

	g[i + n * type[pos1]].push_back(j + n * (1 - type[pos2]));

	gr[j + n * (1 - type[pos2])].push_back(i + n * type[pos1]);

	g[j + n * type[pos2]].push_back(i + n * (1 - type[pos1]));
	
	gr[i + n * (1 - type[pos1])].push_back(j + n * type[pos2]);
}

void build() {
	for (int i = 0; i < n; i++) {
		type[rpos[i][0]] = 0;
		type[rpos[i][1]] = 1;
	}	

	for (int i = 0; i < 2 * n; i++) {
		relax(i, (i + 1) % (2 * n));
	}
}

bool used[MAXN];
int color[MAXN];
vector<int> order;

void dfs_order(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i])
			dfs_order(i);
	}
	order.push_back(v);
}

void dfs_color(int v, int c) {
	color[v] = c;
	used[v] = true;
	for (auto i : gr[v]) {
		if (!used[i]) {
			dfs_color(i, c);
		}
	}
}

void no() {
	cout << "NO\n";
	exit(0);
}

vector<int> ans;

void run() {
	build();
	for (int i = 0; i < 2 * n; i++) {
		if (!used[i])
			dfs_order(i);
	}

	for (int i = 0; i < MAXN; i++)
		used[i] = false;

	reverse(order.begin(), order.end());
	int c = 0;
	
	for (auto i : order) {
		if (!used[i])
			dfs_color(i, c++);
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == color[i + n])
			no();
	}

	for (int i = 0; i < n; i++) {
		if (color[i] > color[i + n])
			ans.push_back(rpos[i][0]);
		else
			ans.push_back(rpos[i][1]);
	}
}

void write() {
	cout << "YES\n";
	for (auto i : ans)
		cout << i + 1 << " ";
	cout << "\n";
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