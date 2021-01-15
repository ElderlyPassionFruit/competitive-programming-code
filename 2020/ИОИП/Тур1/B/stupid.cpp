#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

bool check(vector<int> a) {
	vector<int> b = a;
	sort(all(b));
	return b == a;
}

bool check(int mask) {
	vector<int> x;
	vector<int> y;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			x.push_back(a[i]);
		}
		else {
			y.push_back(a[i]);
		}
	}
	/*if (mask == 3552) {
		cout << "x = " << endl;
		for (auto i : x)
			cout << i << " ";
		cout << endl;
	}*/
	if (!check(x)) return false;
	x.resize(unique(all(x)) - x.begin());
	int l = x[0];
	int r = x.back();
	for (auto i : y) {
		if (i > l && i < r) return false;
	}
	return true;
}

int get(int mask) {
	int ans = 0;
	while (mask) {
		ans += mask % 2;
		mask /= 2;
	}
	return ans;
}

int ans;

void run() {
	ans = 0;
	for (int i = 1; i < (1 << n); i++) {
		if (check(i)) {
			if (get(i) == 6) {
			//	cout << "i = " << i << endl;
			}
			chkmax(ans, get(i));
		}
	}
}

void write() {
	cout << n - ans << endl;
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