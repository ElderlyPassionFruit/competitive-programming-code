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
}

int ans;

void run() {
	ans = 0;
	sort(all(a));
	while (!a.empty()) {
		if (a.size() >= 3 && a[a.size() - 1] - a[a.size() - 3] <= 10) {
			ans++;
			a.pop_back();
			a.pop_back();
			a.pop_back();
			continue;
		}
		if (a.size() >= 2 && a[a.size() - 1] - a[a.size() - 2] <= 20) {
			ans++;
			a.pop_back();
			a.pop_back();
			continue;
		}
		ans++;
		a.pop_back();
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