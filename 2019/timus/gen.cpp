#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

void read() {
	int n = get(1, 3);
	int m = get(1, n);
	int k = get(1, m);
	cout << n << " " << m << " " << k << endl;
	for (int i = 0; i < n; i++) {
		cout << get(1, 5) << " " << get(0, 1) << " " << get(0, 1) << endl;
	}
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


/*
6 2 2
1 2 2
2 3 2
3 4 2
1 5 2
4 6 1
2 2
3 1



*/