#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int mnN, mxN, mnS, mxS, T, D;

void no() {
	cout << "NO\n";
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> mnN >> mxN >> mnS >> mxS >> T >> D;
	if (mnN < mnS) no();
	if (mxN > mxS && (mxN - mxS) * T >= D) no();
	cout << "YES\n";
	return 0;
}