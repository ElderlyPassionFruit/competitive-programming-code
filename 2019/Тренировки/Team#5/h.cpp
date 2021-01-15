#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a, b, c;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	b.resize(n);
	for (auto &i : b)
		cin >> i;
	cin >> k;
	c.resize(k);
	for (auto &i : c)
		cin >> i;
}

int ans;

void run() {
	ans = 0;
	for (auto i : c)
		ans += i;

	int mx_a = 0;
	for (auto i : a)
		chkmax(mx_a, i);
	ans += mx_a * k;
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