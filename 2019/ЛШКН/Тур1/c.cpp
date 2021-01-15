#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<pair <int, int> > a;
void read() {
	cin >> n >> m;
	a.resize(m);
	for (auto &i : a)
		cin >> i.first >> i.second;
}

int ans;

void run() {
	int l = 1, r = n;
	for (auto &i : a) {
		if (i.first > i.second)
			swap(i.first, i.second);
		chkmax(l, i.first);
		chkmin(r, i.second);
	}
	ans = max(0LL, r - l);
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