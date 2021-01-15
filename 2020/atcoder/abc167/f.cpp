#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

pair<int, int> read_string() {
	string s;
	cin >> s;
	int bal = 0;
	int min_bal = 0;
	for (auto i : s) {
		if (i == '(') {
			bal++;
		} else {
			bal--;
		}
		chkmin(min_bal, bal);
	}
	return {min_bal, bal};
}

int n;
vector<pair<int,int>> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		i = read_string();
	}
}	

void no() {
	cout << "No\n";
	exit(0);
}

void check() {
	int bal = 0;
	for (auto i : a) {
		if (bal + i.first < 0) return;
		bal += i.second;
	}
	if (bal != 0) return;
	cout << "Yes\n";
	exit(0);
}

int sign(int x) {
	if (x >= 0) return 1;
	return -1;
}

void run() {
	sort(all(a), [&] (pair<int, int> i, pair<int, int> j) {
		if (sign(i.second) != sign(j.second)) return sign(i.second) > sign(j.second);
		if (sign(i.second) >= 0) return i.first > j.first;
		return i.first - i.second < j.first - j.second;
	});
	check();
}

void write() {
	cout << "No\n";
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
