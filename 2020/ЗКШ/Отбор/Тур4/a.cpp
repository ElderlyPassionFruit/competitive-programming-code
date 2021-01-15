#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
map<char, multiset<string> > s;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string a;
		cin >> a;
		s[a[0]].insert(a);
	}
}

void run() {

}

void write() {
	cout << s.size() << endl;
	for (auto i : s) {
		for (auto j : i.second)
			cout << j << " ";
		cout << endl;
	}
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