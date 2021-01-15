#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

const int MX = 5;

void genPoint() {
	int x = 0, y = 0, z = 0;
	int val = get(1, 3);
	if (val == 1) x = 1;
	else if (val == 2) y = 1;
	else if (val == 3) z = 1;
	cout << x + get(0, MX) << " " << y + get(0, MX) << " " << z + get(0, MX) << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	genPoint();
	int n = get(1, MX);
	cout << n << endl;
	int cnt = 0;
	vector<bool> used(n, false);
	for (int i = 0; i < n; i++) {
		int t;
		t = get(1, 2);
		if (t == 2) {
			bool ok = false;
			for (int j = 0; j < cnt; j++) {
				if (!used[j]) {
					ok = true;
					break;
				}
			}
			if (!ok) {
				t = 1;
			}
		} 
		if (t == 1) {
			cout << "A ";
			genPoint();
			cnt++;
		} else {
			int pos = get(0, cnt - 1);
			while (used[pos]) {
				pos = get(0, cnt - 1);
			} 
			cout << "R " << pos + 1 << endl; 
		}
	}
	return 0;
}