#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct point
{
	
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (auto &i : a)
		cin >> i;
	for (auto &i : b)
		cin >> i;
	int x = solve(a, b);
	int y = solve(b, a);
	//cout << x << " " << y << endl;
	if (x * 2 > n && y * 2 > n) {
		cout << "Both";
	}
	else if (x * 2 > n && y * 2 <= n) {
		cout << "First";
	}
	else if (x * 2 <= n && y * 2 > n) {
		cout << "Second";
	}
	else {
		cout << "None";
	}
	return 0;
}