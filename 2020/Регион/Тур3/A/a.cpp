#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
ll A;
vector<pair<ll, int>> a;

void read() {
	cin >> n >> A;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
}

ll ans;
int pos1, pos2;

void run() {
	sort(all(a));
	ans = 0;
	for (int i = 1; i < n; i++) {
		int pos = --upper_bound(all(a), make_pair(A / a[i].first, n + 1)) - a.begin();
		pos = min(pos, i - 1);
		if (pos != -1 && ans < a[i].first * a[pos].first && a[i].first * a[pos].first <= A) {
			ans = a[i].first * a[pos].first;
			pos1 = a[pos].second;
			pos2 = a[i].second;
		}
	}
}

void write() {
	cout << ans << endl;
	if (ans)
	cout << pos1 + 1 << " " << pos2 + 1 << endl;
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