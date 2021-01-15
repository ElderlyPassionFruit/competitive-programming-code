#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int a, b, c, d;

void yes() {
	cout << "YES" << endl;
	exit(0);
}

void no(vector<pair<int, int> > ans) {
	cout << "NO" << endl;
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i.first << " " << i.second << endl;
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	//freopen("knight.in", "r", stdin);
	//freopen("knight.out", "w", stdout);
	cin >> a >> b >> c >> d;
	if (c == 1 && d == 1) {
		yes();
	}
	else if (c > a && a == 1) {
		no({{0, 1}, {0, -1}});
	}
	else if (d > b && b == 1) {
		no({{1, 0}, {-1, 0}});
	}
	else if (a > c || b > d) {
		no({{a - 1, b - 1}, {-1, 0}, {0, -1}});
	}
	else { 
		yes();
	}
	return 0;
}