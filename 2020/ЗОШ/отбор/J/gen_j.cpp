#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

mt19937 rnd(time(0));

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

const int MAXN = 10;

void gen() {
	int n = get(MAXN, MAXN);
	cout << n << endl;
	set<pair<int, int> > a;
	for (int i = 0; i < n; i++) {
		pair<int,int> x = {get(1, MAXN), get(1, MAXN)};
		while (a.count(x)) {
			x = {get(1, MAXN), get(1, MAXN)};
		}
		a.insert(x);
		cout << x.first << " " << x.second << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	int t = get(1, 1);
	cout << t << endl;
	while (t--)
		gen();

	return 0;
}