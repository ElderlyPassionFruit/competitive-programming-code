#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;

void read() {
	cin >> n >> k;
}

ld ans;

void run() {
	ans = 0;
	for (int i = 1; i <= n; i++)
		ans += i;
	ans /= n;
	for (int i = 1; i < k; i++) {
		ld sum = 0;
		for (int i = 1; i <= n; i++)
			if (i <= ans)
				sum += ans;
			else
				sum += i; 
		ans = sum / n;
	}
}

void write() {
	cout.precision(20);
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