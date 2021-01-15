#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n;
int l;

void read() {
	cin >> n >> l;
}

int POW(int a, int n) {
	int ans = 1;
	for (int i = 0; i < n; i++)
		ans *= a;
	return ans;
}

void run() {
	for (int i = 1; i <= 20; i++) {
		if (POW(i, l) >= n) {
			cout << i << endl;
			exit(0);
		}
	}
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