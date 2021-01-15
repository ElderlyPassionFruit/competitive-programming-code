#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
vector<ll> fact(ll x) {
	vector<ll> ans;
	for (int i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			ans.push_back(i);
			ans.push_back(x / i);
		}
	}
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	return ans;
}

ll x;

void read() {
	cin >> x;
}

ll lcm(ll a, ll b) {
	return a / __gcd(a, b) * b;
}

pair<int, int> ans;

void run() {
	ans = {1, x};
	vector<ll> a = fact(x);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (lcm(a[i], a[j]) == x) {
				if (max(a[i], a[j]) < max(ans.first, ans.second)) {
					ans = {a[i], a[j]};
				}
			}
		}
	}
}

void write() {
	cout << ans.first << " " << ans.second << endl;
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