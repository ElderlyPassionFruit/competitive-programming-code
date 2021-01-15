#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n;
vector<int> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) cin >> i;
}

int calc(int mask) {
	int ans = 0;
	int k = __builtin_popcount(mask);
	if (!k) return 0;
	for (int bit = 0; bit < 60; bit++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if ((mask >> i) & 1) {
				cnt += (a[i] >> bit) & 1;
			}
		}
		if (cnt >= max(1LL, k - 2)) {
			ans += 1LL << bit;
		}
	}
	return ans;
}

int ans;

string write(int mask) {
	string ans = "";
	for (int i = 0; i < n; i++) {
		ans += mask % 2 + '0';
		mask /= 2;
	}
	reverse(all(ans));
	return ans;
}

void run() {
	ans = 0;
	//for (auto i : a) {
	//	cout << write(i) << endl;
	//}
	//cout << endl;
	for (int mask = 0; mask < (1 << n); mask++) {
		chkmax(ans, calc(mask));
		//if (calc(mask) == 15) {
		//	cout << write(mask) << endl;
		//}
	}
	//cout << "ans = " << write(ans) << endl;
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