#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
}

int sz;
vector<int> ans;

void solve(vector<int> have, vector<int> fans, int level) {
	if (fans.size() >= sz) return;
 	have.resize(unique(all(have)) - have.begin());
	if (have.size() == 1 && have.back() == 0) {
		if (sz > fans.size()) {
			ans = fans;
			sz = ans.size();
		}
		return;
	}
	bool flag = false;
	for (auto i : have) {
		flag |= (abs(i % 2) == 1);
	}

	if (!flag) {
		for (auto &i : have) {
			i /= 2;
		}
		solve(have, fans, level + 1);
		return;
	}

	vector<int> a = have;

	for (auto &i : a) {
		if (i % 2) {
			i--;
		}
		i /= 2;
	}

	fans.push_back((1 << level));
	if (a != have) {
		solve(a, fans, level + 1);
	}

	a = have;
	for (auto &i : a) {
		if (i % 2) {
			i++;
		}
		i /= 2;
	}
	fans.pop_back();
	fans.push_back(-(1 << level));
	if (a != have) {
		solve(a, fans, level + 1);
	}
}

void run() {
	sz = 1e9;
	solve(a, {}, 0);
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
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