#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 20;
struct segment{
	int l, r, cost;
	segment() {}
};

bool operator<(const segment & a, const segment & b) {
	return a.r < b.r;
}

int n, k;
vector<segment> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.l >> i.r >> i.cost;
	}
	sort(all(a));
}

ll dp[MAXN];
const ll INF = 2e9 + 228;
ll ans = INF;

bool check(ll fans) {
	for (int i = 0; i < n; i++)
		dp[i] = INF;

	for (int i = 0; i < n; i++) {
		if (a[i].cost > fans) continue;
		if (a[i].l == 1) {
			dp[i] = -INF;
			continue;
		}
		for (int j = 0; j < i; j++) {
			if (a[j].l >= a[i].l || a[j].r + 1 < a[i].l) continue;
			if (dp[j] >= a[i].l) continue;
			if (a[j].cost + a[i].cost > fans && a[j].r >= a[i].l) continue;
			chkmin(dp[i], a[j].r);
		}
	}
	/*cout << "dp = " <<  endl;
	for (int i = 0; i < n; i++)
		cout << dp[i] << " ";
	cout << endl;
	*/
	for (int i = 0; i < n; i++) {
		if (a[i].r == k && dp[i] != INF) {
			return true;
		}
	}
	return false;
}

void run() {
	//cout << check(1) << endl;
	//exit(0);
	ll l = 0, r = INF;
	while (l < r - 1) {
		ll mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = r;
}

void write() {
	if (ans == INF)
		ans = -1;
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