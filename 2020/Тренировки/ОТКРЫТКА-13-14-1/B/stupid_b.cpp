#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define int ll
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 20;
vector<pair<int, int>> edge;
int n, m;
int p[MAXN];
set<pair<int, int>> check;
void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	edge.resize(m);
	for (auto &i : edge) {
		cin >> i.first >> i.second;
		check.insert({min(i.first, i.second), max({i.first, i.second})});
	}
	assert(check.size() == m);
	for (int i = 0; i < m; i++) {
		edge.push_back({edge[i].second, edge[i].first});
	}
}

int ans;
vector<int> fans;

void relax(vector<int> v) {
	set<int> have;
	for (auto i : v) {
		have.insert(i);
	}
	if (have.size() != v.size()) return;
	int Fans = 0;
	for (auto i : v) {
		Fans += p[i];
	}
	if (ans < Fans) {
		ans = Fans;
		fans = v;
	}
}

void run() {
	ans = -1e18;
	for (int i = 1; i <= n; i++) relax({i});

	for (auto i : edge) {
		relax({i.first, i.second});
		for (auto j : edge) {
			if (j.first != i.second) continue;
			relax({i.first, i.second, j.second});
			for (auto k : edge) {
				if (k.first != j.second) continue;
				relax({i.first, i.second, j.second, k.second});
			}
		}
	}
}

void write() {
	cout << ans << endl;
	cout << fans.size() << endl;
	for (auto i : fans) {
		cout << i << " ";
	}
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