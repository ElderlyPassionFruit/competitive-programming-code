#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e3 + 10;
ll a[MAXN][MAXN][2];

void read() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			for (int k = 0; k < 2; k++) {
				a[i][j][k] = 1;
			}
		}
	}
}

void run() {

}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}