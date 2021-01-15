#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

struct edge{
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to;
		cost = _cost;
	}
};

const int MAXN = 1e5 + 10;
vector<edge> gL[MAXN], gR[MAXN];
int n;
int need;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int to, cost;
		cin >> to >> cost;
		if (to != 0) {
			to--;
			gL[i].push_back({to, cost});
		}
		cin >> to >> cost;
		if (to != 0) {
			to--;
			gR[i].push_back({to, cost});
		}
	}

	cin >> need;
	need--;
}

const int INF = 2e9 + 228;

int ans;
bool flag;

void dfs(int v, int have) {
	//cout << v << " " << have << endl;
	if (have && v == need) {
		flag = true;
	}
	if (gL[v].empty() || gR[v].empty()) {
		for (auto i : gL[v]) {	
			int add = min(have, i.cost);
			have -= add;
			dfs(i.to, add);
		}
		for (auto i : gR[v]) {	
			int add = min(have, i.cost);
			have -= add;
			dfs(i.to, add);
		}
	}
	else {
		int L = gL[v][0].cost;
		int R = gR[v][0].cost;
		int toL = 0, toR = 0;
		int add;

		if (L > R) {
			add = min(L - R, have);
			L -= add;
			toL += add;
			have -= add;
		} 
		else {
			add = min(R - L, have);
			R -= add;
			toR += add;
			have -= add;
		}

		add = min(L, have / 2);
		L -= add;
		toL += add;
		R -= add;
		toR += add;
		have -= 2 * add;
		if (L && have) {
			toL++;
			have--;
		}

		assert(!(R && have));

		dfs(gL[v][0].to, toL);
		dfs(gR[v][0].to, toR);
	}
	//cout << "last = " << v << " " << have << endl;
}

void run() {
	//dfs(0, 3);
	//exit(0);
	int l = 0, r = INF;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		flag = false;
		dfs(0, mid);
		if (flag) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	if (r == INF) {
		ans = -1;
	}
	else {
		ans = r;
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