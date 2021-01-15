#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
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
	sort(all(a));
	multiset<int> have;
	for (auto i : a)
		have.insert(i);
	ans = 0;
	while (!have.empty()) {
		auto x = *have.begin();
		have.erase(have.begin());
		ans++;
		if (have.find(x + 1) != have.end()) {
			have.erase(have.find(x + 1));
		}
	}
}

void write() {
	cout << ans;
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