#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
}

bool check(string a, string b) {
	multiset<char> haveLa, haveRa, haveLb, haveRb;
	for (int i = 0; i < a.size(); i++) {
		haveLa.insert(a[i]);
		haveLb.insert(b[i]);
	}
	for (int i = a.size() - 1; i >= 1; i--) {
		haveRa.insert(a[i]);
		haveRb.insert(b[i]);
		haveLa.erase(haveLa.find(a[i]));
		haveLb.erase(haveLb.find(b[i]));
		if (haveRa == haveRb && haveLa == haveLb) {
			return false;
		}
	}
	return true;
}

string solve(int l, int r) {
	string a = "";
	for (int i = l; i <= r; i++)
		a += s[i];
	string b = a;
	sort(all(b));
	do {
		if (check(a, b)) {
			return "Yes";
		}
	} while (next_permutation(all(b)));
	return "No";
}

void run() {
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		cout << solve(l, r) << "\n";
	}
}

void write() {

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