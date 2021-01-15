#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MAXN = 2e5 + 10;
int n, k;
int a[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
	}
}

int used[MAXN];
int ans;

void run() {
	fill(used, used + n, -1);
	int now = 0;
	int t = 0;
	while (k > 0 && used[now] == -1) {
		used[now] = t++;
		now = a[now];
		k--;
	}
	if (!k) {
		ans = now;
		return;
	}
	int len = t - used[now];
	k %= len;
	while (k > 0) {
		now = a[now];
		k--;
	}
	ans = now;
}

void write() {
	cout << ans + 1 << endl;
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