#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n, m;
vector<int> c, w;

void read() {
	cin >> n >> m; 
	c.resize(n);
	for (auto &i : c)
		cin >> i;
	w.resize(n);
	for (auto &i : w)
		cin >> i;
}

vector<bool> used;

void build() {
	used.resize(n, false);
}

void calc() {
	set<pair<int, int>> have;
	int now = m;
	for (int i = 0; i < n; i++) {
		if (c[i] % 100 == 0) {
			continue;
		}
		int need = c[i] % 100;
		int get = 100 - need;
		have.insert({w[i] * get, i});
		if (need <= now) {
			now -= need;
			continue;
		}
		auto it = have.begin();
		used[it->second] = true;
		have.erase(have.begin());
		now += 100;
		now -= need;
	}
}

vector<pair<int, int>> ans;
int fans;

void make_ans() {
	fans = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			ans.push_back({c[i] / 100, c[i] % 100});
		} else {
			fans += (100 - c[i] % 100) * w[i];
			ans.push_back({c[i] / 100 + 1, 0});
		}
	}
}

void run() {
	build();
	calc();
	make_ans();
}

void write() {
	cout << fans << "\n";
	for (auto i : ans)
		cout << i.first << " " << i.second << "\n";
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