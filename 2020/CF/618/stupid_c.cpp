#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

vector<ld> ans;

void run() {
	int pos = 0;
	while (pos < n) {
		int r = pos;
		ld sum = a[pos];
		int now = a[pos];
		int len = 1;
		for (int i = pos + 1; i < n; i++) {
			now += a[i];
			len++;
			if ((ld) now / len < sum) {
				sum = (ld)now / len;
				r = i;
			}
		}
		for (int i = pos; i <= r; i++)
			ans.push_back(sum);
		pos = r + 1;
	}
}

void write() {
	cout.precision(12);
	cout.setf(ios::fixed);
	for (auto i : ans)
		cout << i << "\n";
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