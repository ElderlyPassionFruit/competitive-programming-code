#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

string gen() {
	int len = get(1, 4);
	string s = "";
	for (int i = 0; i < len; i++) {
		if (rnd() & 1) {
			s += "(";
		} else {
			s += ")";
		}
	}
	return s;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n = get(5, 5);
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		cout << gen() << endl;
	}
	return 0;
}