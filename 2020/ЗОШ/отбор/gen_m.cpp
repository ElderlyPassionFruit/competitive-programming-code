#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

mt19937 rnd(time(0));

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

const int MAXN = 10;

int n, m, q;
vector<set<int> > g;

pair<int, int> get_edge() {
	while (true) {
		int x = get(1, n);
		int y = get(1, n);
		if (x == y) continue;
		if (g[x].size() >= 2) continue;
		if (g[y].size() >= 2) continue;
		if (g[x].count(y)) continue;
		g[x].insert(y);
		g[y].insert(x);
		return {x, y};
	}
}

pair<int, int> del_edge() {
	while (true) {
		int x = get(1, n);
		int y = get(1, n);
		if (!g[x].count(y)) continue;
		g[x].erase(y);
		g[y].erase(x);
		return {x, y};
	}
}

pair<int, int> get_q() {
	return {get(1, n), get(1, n)};
}

bool check_add() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += (g[i].size() < 2);
	}
	return ans >= 2;
}

bool check_del() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += g[i].size();
	}
	return ans;
}

vector<char> var = {'+', '-', '?'};

char get_type() {
	while (true) {
		char type = var[get(0, 2)];
		if (type == '+' && !check_add()) continue;
		if (type == '-' && !check_del()) continue;
		return type;
	}
} 

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	n = get(1, MAXN);
	m = get(1, n - 1);
	q = get(1, MAXN);
	cout << n << " " << m << " " << q << endl;
	g.resize(n + 1);
	for (int i = 0; i < m; i++) {
		auto x = get_edge();
		cout << x.first << " " << x.second << endl;
	}
	for (int i = 0; i < q; i++) {
		char type = get_type();
		cout << type << " ";
		pair<int, int> x;
		if (type == '+') x = get_edge();
		if (type == '-') x = del_edge();
		if (type == '?') x = get_q();
		cout << x.first << " " << x.second << endl;
	}
	return 0;
}