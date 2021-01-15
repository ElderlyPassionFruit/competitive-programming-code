#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1101;
int mem[N][N][5];

// 0 - 111, 1 - 101, 2 - 110, 3 - 010, 4 - 100
// 0 - UnUsed, 1 - Win, 2 - Lose

int calcDp(int A, int B, int type) {
	if (A < 0 || B < 0) return -1;
	if (mem[A][B][type]) return mem[A][B][type];
	bool ok = false;

	if (type == 0) {
		ok |= calcDp(A, B + 1, 3) == 2;
		ok |= calcDp(A, B + 1, 4) == 2;
		ok |= calcDp(A, B, 3) == 2;
		ok |= calcDp(A, B, 4) == 2;
		
		ok |= calcDp(A + 1, B - 1, 3) == 2;
		ok |= calcDp(A + 1, B - 1, 4) == 2;
	} else if (type == 1) {
		ok |= calcDp(A - 1, B + 1, 0) == 2;
		ok |= calcDp(A - 1, B, 0) == 2;
		ok |= calcDp(A - 1, B + 1, 3) == 2;
		ok |= calcDp(A - 1, B, 3) == 2;
		ok |= calcDp(A - 1, B + 1, 4) == 2;
		ok |= calcDp(A - 1, B, 4) == 2;

		ok |= calcDp(A, B - 1, 0) == 2;
		ok |= calcDp(A, B - 1, 3) == 2;
		ok |= calcDp(A, B - 1, 4) == 2;
	} else if (type == 2) {
		ok |= calcDp(A - 1, B + 1, 0) == 2;
		ok |= calcDp(A - 1, B, 0) == 2;
		ok |= calcDp(A - 1, B + 2, 3) == 2;
		ok |= calcDp(A - 1, B + 1, 3) == 2;
		ok |= calcDp(A - 1, B + 2, 4) == 2;
		ok |= calcDp(A - 1, B + 1, 4) == 2;

		ok |= calcDp(A, B - 1, 0) == 2;
		ok |= calcDp(A, B, 3) == 2;
		ok |= calcDp(A, B, 4) == 2;
	} else if (type == 3) {
		ok |= calcDp(A - 1, B + 1, 2) == 2;
		ok |= calcDp(A - 1, B, 2) == 2;
		ok |= calcDp(A - 1, B + 1, 3) == 2;
		ok |= calcDp(A - 1, B, 3) == 2;
		ok |= calcDp(A - 1, B + 1, 4) == 2;
		ok |= calcDp(A - 1, B, 4) == 2;

		ok |= calcDp(A, B - 1, 2) == 2;
		ok |= calcDp(A, B - 1, 3) == 2;
		ok |= calcDp(A, B - 1, 4) == 2;
	} else if (type == 4) {
		ok |= calcDp(A - 1, B + 1, 1) == 2;
		ok |= calcDp(A - 1, B, 1) == 2;
		ok |= calcDp(A - 1, B + 1, 2) == 2;
		ok |= calcDp(A - 1, B, 2) == 2;

		ok |= calcDp(A, B - 1, 2) == 2;
		ok |= calcDp(A, B - 1, 1) == 2;
	}

	if (ok) mem[A][B][type] = 1;
	else mem[A][B][type] = 2;
	return mem[A][B][type];
}

int readType() {
	int a, b, c;
	cin >> a >> b >> c;
	if (a && b && c) return 0;
	if (a && c) return 1;
	if (b && (a || c)) return 2;
	if (b) return 3;
	assert(a || c);
	return 4;
}

signed main() {
    freopen("jenga.in", "r", stdin);
    freopen("jenga.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	int A = 0, B = 0;
	for (int i = 0; i < n - 1; i++) {
		int t = readType();
		if (t == 0) A++;
		if (t == 2) B++;
	}
	int top = readType();	
	if (calcDp(A, B, top) == 1) {
		cout << "Alex\n";
	} else {
		cout << "Igor\n";
	}
	return 0;
}