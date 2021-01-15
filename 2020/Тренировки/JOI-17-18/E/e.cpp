#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm,popcnt")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, q;
string s;
int sum = 0;

void read() {
	cin >> n >> q;
	cin >> s;
	for (int i = 0; i < (1 << n); i++)
		s[i] = s[i] - '0';
	for (auto i : s) sum += i;
}

const int MAXN = 13;

int dp[1 << MAXN];

void build() {

}

bool check_submask(int mask, int submask) {
	return (mask & submask) == submask;
}

int upmask(int mask) {
	int ans = 0;
	for (int i = 0; i < (1 << n); i++) {
		if (check_submask(i, mask)) {
			ans += s[i];
		}
	}
	return ans;
}

int submask(int mask) {
	int ans = 0;
	for (int i = 0; i < (1 << n); i++) {
		if (check_submask(mask, i)) {
			ans += s[i];
		}
	}
	return ans;
}

int get(int mask) {
	return __builtin_popcount(mask);
}

void solve() {
	string s;
	cin >> s;
	int mask0 = 0, mask1 = 0, mask2 = 0;
	for (int i = 0; i < n; i++) {
		mask0 *= 2;
		mask1 *= 2;
		mask2 *= 2;
		if (s[i] == '0') mask0++;
		else if (s[i] == '1') mask1++;
		else mask2++;
	}

	int x0 = get(mask0), x1 = get(mask1), x2 = get(mask2);
	int ans;
	ans = 0;
	if (min({x0, x1, x2}) == x0) {
		for (int mask = mask0; mask >= 0; mask = (mask - 1) & mask0) {
			if (get(mask) % 2 != get(mask0) % 2) ans -= upmask((mask0 ^ mask) | mask1);
			else ans += upmask((mask0 ^ mask) | mask1);
			if (!mask) break;
		}
	}
	else if (min({x0, x1, x2}) == x1) {
		for (int mask = mask1; ; mask = (mask - 1) & mask1) {
			if (get(mask) % 2 == get(mask1) % 2) ans += submask(mask | mask2);
			else ans -= submask(mask | mask2);
			if (!mask) break;	
		}
	}
	else {
		for (int mask = mask2; ; mask = (mask - 1) & mask2) {
			ans += s[mask1 | mask];
			if (!mask) break;
		}
	}
	cout << ans << "\n";
}

void run() {
	build();
	while (q--) {
		solve();
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	return 0;
}