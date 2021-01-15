#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

const int MAXA = 2010;

int have[MAXA];

int get(int s) {
	for (auto i : a)
		if (s > i)
			have[s - i]++;

	int ans = 0;

	for (int i = 1; i <= s / 2; i++) {
		if (i != s - i)
		ans += min(have[i], have[s - i]);
		else
		ans += have[i] / 2;
	}

	for (auto i : a)
		if (s > i)
			have[s - i]--;
	return ans;
}

int ans;

void run() {
	ans = 0;
	for (int s = 2; s <= 2000; s++) {
		chkmax(ans, get(s));
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