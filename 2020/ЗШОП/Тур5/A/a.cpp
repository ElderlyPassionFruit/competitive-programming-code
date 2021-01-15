#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ull

int n, k;

void read() {
	cin >> n >> k;
}

string solve(int n, int k) {
	if (n == 1) { 
		if (k == 0) return "0";
		else return "1";
	}
	if ((1LL << (n - 1)) > k) {
		return "0" + solve(n - 1, k);
	}
	else {
		k -= (1LL << (n - 1));
		k = (1LL << (n - 1)) - k - 1;
		string ans = solve(n - 1, k);
		return "1" + ans;
	}
}

string ans;

void run() {
	ans = solve(n, k);
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