#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

using matrix = vector<vector<int>>;
const int INF = 1e18 + 228 + 1337;

matrix mul(const matrix & a, const matrix & b) {
	int n = a.size();
	matrix ans(n, vector<int> (n, INF));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int h = 0; h < n; h++) {
				ans[i][j] = min(ans[i][j], a[i][h] + b[h][j]);
			}
		}
	}
	return ans;
}

matrix binpow(matrix a, int n) {
	if (n == 1) return a;
	if (n & 1) {
		return mul(a, binpow(a, n - 1));
	} else {
		return binpow(mul(a, a), n / 2);
	}
}

const int BUBEN = 100;
int a[BUBEN], b[BUBEN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	matrix ans(BUBEN, vector<int> (BUBEN, INF));
	for (int i = 0; i < BUBEN; i++) { 
		ans[i][i] = 0;
	}
	for (int i = 0; i < n; i++) {
		matrix now(BUBEN,  vector<int> (BUBEN, INF));
		for (int x = 0; x < BUBEN - 1; x++) {
			now[x + 1][x] = b[i];
			now[x][x + 1] = a[i];
		}
		ans = mul(ans, now);
	}
	ans = binpow(ans, m);
	cout << ans[0][0] << endl;
	return 0;
}