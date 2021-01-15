#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n;
vector<int> g[MAXN];
int l[MAXN], r[MAXN];

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
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
	} 
}

bool ans[MAXN];

struct event{
	int l, r;
	bool flag;
	event() {}
	event(int a, int b, bool c) {
		l = a, r = b, flag = c;
	}
};

const int INF = 1e10;

event dfs(int v, int p) {
	event fans(-INF, INF, true);
	for (auto i : g[v]) {
		if (i != p) {
			auto x = dfs(i, v);
			fans.flag &= x.flag;
			chkmax(fans.l, x.l);
			chkmin(fans.r, x.r);
		}
	}
	if (fans.l == -INF && fans.r == INF) {
		fans.l = 0;
		fans.r = 0;
	}
	fans.flag &= (fans.l <= fans.r);
	fans.l += l[v];
	fans.r += r[v];
	//cout << "v = " << v << endl;
	//cout << "fans = " << fans.l << " " << fans.r << " " << fans.flag << endl;
	return fans;
}

void run() {
	//dfs(4, 4);
	//return;
	for (int i = 0; i < n; i++) {
		ans[i] = dfs(i, i).flag;
	}
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
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
