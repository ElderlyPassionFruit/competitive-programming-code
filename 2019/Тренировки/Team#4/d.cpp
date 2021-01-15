#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;
int x[MAXN], r[MAXN], c[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> r[i] >> c[i];
	}
}

bool check(int ind) {
	return (x[ind] - x[ind - 1]) <= c[ind - 1] * r[ind - 1];
}

int ans;

void run() {
	ans = 1;
	for (int i = 1; i < n; i++) {
		if (check(i))
			continue;
		ans++;
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