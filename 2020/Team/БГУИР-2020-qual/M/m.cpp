#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

bool operator==(const pt & a, const pt & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

const int MAXN = 1010;
pt par[MAXN][MAXN];

void make() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			par[i][j] = {i, j};
		}
	}
}

pt get_par(pt v) {
	if (par[v.x][v.y] == v) return v;
	return par[v.x][v.y] = get_par(par[v.x][v.y]);
}


void uni(pt a, pt b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return;
	par[a.x][a.y] = b;
}

int n, m;
char table[MAXN][MAXN];

void make(vector<pt> a) {
	if (a.size() <= 2) return;
	if (a.size() == 3) {
		uni(a[0], a[2]);
		return;
	}
	for (int i = 0; i + 1 < (int)a.size(); i++) {
		uni(a[i], a[i + 1]);
	}
}

void build() {
	for (int i = 1; i <= n; i++) {
		vector<vector<pt>> have(26);
		for (int j = 1; j <= m; j++) {
			have[table[i][j] - 'a'].push_back({i, j});
		}
		for (auto x : have) make(x);
	}

	for (int j = 1; j <= m; j++) {
		vector<vector<pt>> have(26);
		for (int i = 1; i <= n; i++) {
			have[table[i][j] - 'a'].push_back({i, j});
		}
		for (auto x : have) make(x);
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	make();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
		}
	}
	build();

	int q;
	cin >> q;
	while (q--) {
		pt a, b;
		cin >> a.x >> a.y >> b.x >> b.y;
		a = get_par(a);
		b = get_par(b);
		if (a == b) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
	}

	return 0;
}