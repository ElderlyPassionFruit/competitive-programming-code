#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 1010;
int w, h, n;
int x[MAXN], y[MAXN], r[MAXN];

int sq(int x) {
	return x * x;
}

bool check(int u, int v) {
	return sq(x[u] - x[v]) + sq(y[u] - y[v]) <= sq(r[u] + r[v]);
}

int par[MAXN];

int getPar(int v) {
	if (par[v] == v) return v;
	return par[v] = getPar(par[v]);
}

void uni(int a, int b) {
	par[getPar(a)] = getPar(b);
}

int mnX[MAXN], mxX[MAXN], mnY[MAXN], mxY[MAXN];

bool check(int ind) {
	if (mnX[ind] <= 0 && mxX[ind] >= w) return true;
	if (mnY[ind] <= 0 && mxY[ind] >= h) return true;
	if (mnX[ind] <= 0 && mnY[ind] <= 0) return true;
	if (mxX[ind] >= w && mxY[ind] >= h) return true;
	return false;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> w >> h >> n;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> r[i];
	}	
	iota(par, par + n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (check(i, j)) {
				uni(i, j);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		mnX[i] = mnY[i] = 1e9;
		mxX[i] = mxY[i] = -1e9;
	}
	for (int i = 0; i < n; i++) {
		int pos = getPar(i);
		mnX[pos] = min(mnX[pos], x[i] - r[i]);
		mxX[pos] = max(mxX[pos], x[i] + r[i]);
		mnY[pos] = min(mnY[pos], y[i] - r[i]);
		mxY[pos] = max(mxY[pos], y[i] + r[i]);
	}
	for (int i = 0; i < n; i++) {
		if (check(getPar(i))) {
			cout << "N" << endl;
			return 0;
		}
	}
	cout << "S" << endl;
	return 0;
}