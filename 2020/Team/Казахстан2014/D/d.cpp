#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1000;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) {
		a += MOD;
	}
	return a;
}

int mul(int a, int b) {
	return a * b % MOD;
}

const int MAXN = 2000;

int cnk[MAXN][MAXN];

void build() {
	cnk[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		cnk[i][0] = 1;
		for (int j = 1; j < MAXN; j++) {
			cnk[i][j] = add(cnk[i - 1][j - 1], cnk[i - 1][j]);
		}
	}
	for (int j = 0; j < MAXN; j++) {
		cout << cnk[MAXN - 1][j] << " ";
	}
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	return 0;
}