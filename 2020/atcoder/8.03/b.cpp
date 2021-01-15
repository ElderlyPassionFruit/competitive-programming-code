#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int A, B, M;
vector<int> a, b;

void read() {
	cin >> A >> B >> M;
	a.resize(A);
	for (auto &i : a) {
		cin >> i;
	}
	b.resize(B);
	for (auto &i : b) {
		cin >> i;
	}
}

int ans;

void run() {
	ans = *min_element(all(a)) + *min_element(all(b));
	while (M--) {
		int x, y, c;
		cin >> x >> y >> c;
		x--;
		y--;
		chkmin(ans, a[x] + b[y] - c);
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}