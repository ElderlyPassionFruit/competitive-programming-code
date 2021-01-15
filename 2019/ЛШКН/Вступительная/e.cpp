#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double

const double EPS = 1e-9;
bool check(double a1, double a2, double a3, double A, double B) {
	if (abs(-2 * A - B - a1) > EPS)
		return false;
	if (abs(2 * A * B + A * A - a2) > EPS)
		return false;
	if (abs(-A * A * B - a3) > EPS)
		return false;
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	double a0, a1, a2, a3;
	cin >> a0 >> a1 >> a2 >> a3;
	a1 /= a0;
	a2 /= a0;
	a3 /= a0;

	double D = a1 * a1 - 3 * a2;
	if (D < 0) {
		cout << "No\n";
		return 0;
	}

	D = sqrt(D);
	double A = -a1 + D;
	A /= 3.0;
	double B = -a1 - 2 * A;
	
	if (check(a1, a2, a3, A, B)) {
		cout << "Yes\n";
		return 0;
	}

	A = -a1 - D;
	A /= 3.0;
	B = -a1 - 2 * A;
	
	if (check(a1, a2, a3, A, B)) {
		cout << "Yes\n";
		return 0;
	}
	cout << "No\n";
	return 0;
}