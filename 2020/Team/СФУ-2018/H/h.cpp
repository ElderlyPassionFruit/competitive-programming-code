#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const ll INF = 4e18;

void no() {
	cout << "false" << endl;
	exit(0);
}

void yes() {
	cout << "true" << endl;
	exit(0);
}

int mul(int a, int b) {
	if (a > (INF + b - 1) / b) no();
	return a * b;
}

const int MAXN = 510;
int n, m;
int A[MAXN][MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}

	if (n == 1 && m == 1) {
		yes();
	}

	int a, b;

	if (n == 1) {
		b = A[0][1] - A[0][0];
		if (!b) no();
		if (A[0][0] % b) no();
		a = A[0][0] / b;
	} else {
		a = A[1][0] - A[0][0];
		if (!a) no();
		if (A[0][0] % a) no();
		b = A[0][0] / a;
	}

	swap(a, b);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x = mul((a + i), (b + j));
			if (x != A[i][j]) no();
		}
	}
	yes();
	return 0;
}