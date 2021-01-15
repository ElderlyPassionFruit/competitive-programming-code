#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
const int MAXN = 10;
int cost[MAXN];

bool check(int x) {
	int ans = 0;
	int nx = x;
	while (x) {
		ans += cost[x % 10];
		x /= 10;
	}
	return ans == nx;
}

void read() {
	cost[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		cost[i] = 1;
		for (int j = 0; j < i; j++) {
			cost[i] *= i;
		}
		cout << "i = " << i << " cost = " << cost[i] << endl;
	}
	for (int i = 1; i <= 1000000000; i++) {
		if (check(i)) {
			cout << i << ",";
			cout.flush();
		}
	}
	int ans = 0;
	int l, r;
	cin >> l >> r;
	vector<int> have = {1,3435,438579088};
	for (auto i : have) {
		if (l <= i && i <= r) {
			ans++;
		}
	}
	cout << ans << endl;
}

void run() {

}

void write() {

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