#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int getVal() {
	return (rnd() % ((int)(1e6) / 60) + 1) * 2;
}

void read() {
	int n = 30;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = getVal();
	}
	sort(all(a));
	a[a.size() - 1]++;
	int mask = rnd() % (1 << n);
	while ((!((mask >> (n - 1)) & 1))) {
		mask = rnd() % (1 << n);
	}
	int x = 0;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			x += a[i];
		}
	}
	cout << n << " " << x << endl;
	for (auto i : a) {
		cout << i << " ";
	}
	cout << endl;
	return;
}

void run() {
	cout << "30 220815\n";
	cout << "464 1510 1672 3322 5596 5786 9236 11288 11328 12702 13290 14296 14302 15188 20012 20028 20128 21352 21780 23378 24104 24430 26280 26568 27374 30412 30792 32046 32504 32919\n";
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}