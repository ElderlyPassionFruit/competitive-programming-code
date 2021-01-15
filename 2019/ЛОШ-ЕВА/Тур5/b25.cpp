#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
int g, s;

struct ed{
	int u, v, g, s;
	ed() {
		u = -1, v = -1, g = 0, s = 0;
	}
	ed(int z, int a, int b, int c) {
		u = z, v = a, g = b, s = c;
	}
};

bool operator<(ed a, ed b) {
	return a.g < b.g || (a.g == b.g && a.s < b.s);
}

vector<ed> gr;

void read() {
	cin >> n >> m >> g >> s;
	for (int i = 0; i < m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;
		b--;
		gr.push_back({a, b, c, d});
	}
	sort(gr.begin(), gr.end());
}

int p[210], sz[210];

void make() {
	for (int i = 0; i < n; i++) 
		p[i] = i, sz[i] = 1;
}

int get_pred(int v) {
	if (v == p[v]) return v;
	return p[v] = get_pred(p[v]);
}

void union_set(int a, int b) {
	a = get_pred(a);
	b = get_pred(b);
	if (a == b) return;
	if (sz[a] < sz[b])
		swap(a, b);
	p[b] = a;
	sz[a] += sz[b];
}

bool check(int cost) {
	for (int i = 0; i < m; i++) {
		make();
		int cnt_gold = gr[i].g;
		int cnt_silver = cost - gr[i].g * g;
		if (cnt_silver < 0)
			return false;
		cnt_silver /= s;

		for (int j = 0; j <= i; j++) {
			if (gr[j].g <= cnt_gold && gr[j].s <= cnt_silver) {
				union_set(gr[j].u, gr[j].v);
			}
		}
		
		int pred = get_pred(0);
		bool flag = true;
		for (int i = 1; i < n; i++) 
			if (get_pred(i) != pred)
				flag = false;
		if (flag) return true;
	}
	return false;
}

const int INF = 1e18 + 10;
int ans;

void run() {
	int l = 0, r = INF;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	ans = r;
}

void write() {
	if (ans == INF)
		ans = -1;
	cout << ans << endl;
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