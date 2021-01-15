#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n, s;
vector<int> a;

void read() { 
	cin >> n >> s;
	a.resize(n);
	for (auto &i : a) 
		cin >> i;
}

bool check(int k) {
	int ans = 0;
	for (auto i : a) {
		ans += max(0LL, k - i);
		if (ans >= s) return true;
	}
	return ans >= s;
}

int ans;

void run() {
	int l = 0, r = 2e18 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = r;
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