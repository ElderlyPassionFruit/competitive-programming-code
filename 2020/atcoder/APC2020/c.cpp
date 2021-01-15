#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n;

void read() {
	cin >> n;
}

bool getZ(int x, int y, int n) {
	//int l = 0, r = n + 1;
	//while (l < r - 1) {
	//	int z = (l + r) / 2;
	//	if (x * x + y * y + z * z + x * y + x * z + y * z <= n) {
	//		l = z;
	//	} else {
	//		r = z;
	//	}
	//}
	//return x * x + y * y + l * l + x * y + x * l + y * l == n;
	for (int z = 1; x * x + y * y + z * z + x * y + x * z + y * z <= n; z++) {
		if (x * x + y * y + z * z + x * y + x * z + y * z == n) {
			return true;
		}
	}
	return false;
}

int get(int n) {
	ll ans = 0;
	for (int x = 1; x * x <= n; x++) {
		for (int y = 1; x * x + y * y + x * y <= n; y++) {
			if (getZ(x, y, n)) {
				ans++;
			}
		}
	}
	return ans;
}

void run() {
	for (int i = 1; i <= n; i++) {
		cout << get(i) << "\n";
	}
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