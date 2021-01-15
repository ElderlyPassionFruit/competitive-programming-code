#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

int MAX = 10;

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int m = get(1, MAX);
	vector<int> b;
	int last = 1;
	for (int i = 0; i < m; i++) {
		last = get(last, max(MAX, last + 1));
		b.push_back(last);
		last++;		
	}

	int n = get(m, MAX);
	vector<int> a(n);
	for (int i = 0; i < m; i++)
		a[i] = 1;
	shuffle(all(a), rnd);
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 0) {
			a[i] = get(1, MAX);
		} else {
			a[i] = b[pos++];
		}
	}

	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		p[i] = get(-MAX, MAX);
	}

	cout << n << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;

	for (auto i : p)
		cout << i << " ";
	cout << endl;

	cout << m << endl;

	for (auto i : b)
		cout << i << " ";

	cout << endl;

	return 0;
}