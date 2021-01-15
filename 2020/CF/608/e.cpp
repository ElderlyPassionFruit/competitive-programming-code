#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

ll k, n;

void read() {
//	cin >> n >> k;
}

bool check(int x, int m) {
	while (x) {
		if (x == m) return true;
		if (x % 2 == 0) x /= 2;
		else x--;
	}
	return false;
}

int get(int m) {
	int cnt = 0;
	for (int j = m; j <= n; j++) {
		cnt += check(j, m);
	}
	return cnt;		
}

ll ans;

void run() {
	for (n = 1; n <= 100; n++) {
		for (int i = 1; i <= n; i++) {
			cout << get(i) << " "; 
		}
		cout << endl;
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