#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << 1 << endl;
	int n = get(2, 10);
	vector<int> cnt(n);
	cnt[0] = 2;
	for (int i = 0; i < n - 2; i++) {
		cnt[rnd() % n]++;
	}
	vector<int> a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < cnt[i]; j++) {
			a.push_back(i + 1);
		}
	}
	shuffle(all(a), rnd);
	cout << n << endl;
	for (auto i : a) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}