#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
#include <random>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int k;
int mod;
string s;

void read() {
	cin >> k >> mod >> s;
}

int get_num(string x) {
	int ans = 0;
	for (auto i : x) {
		ans *= 10;
		ans += i - '0';
		ans %= mod;
	}
	return ans;
}

string get(string x, int l, int r) {
	string ans = "";
	for (int i = l; i <= r; i++) {
		ans += x[i];
	}
	return ans;
}

int calc(string x) {
	for (int i = 0; i < (int)x.size(); i++) {
		if (x[i] == '+') {
			return (calc(get(x, 0, i - 1)) + calc(get(x, i + 1, (int)x.size() - 1))) % mod;
		}
	}
	for (int i = 0; i < (int)x.size(); i++) {
		if (x[i] == '*') {
			return (calc(get(x, 0, i - 1)) * calc(get(x, i + 1, (int)x.size() - 1))) % mod;
		}
	}
	return get_num(x);
}

int ans;

void no() {
	//cout << 0 << endl;
	//exit(0);
	ans = 0;
}

void run() {
	if (s == "Fail") {
		no();
		return;
	}
	ans = 1;
	set<int> have;
	int cnt = 0;
	int last = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] == '=') {
			cnt++;
			//cout << get(s, last, i - 1) << " " << calc(get(s, last, i - 1)) << endl;
			have.insert(calc(get(s, last, i - 1)));
			last = i + 1;
		}
	}
	//cout << cnt << endl;
	if(last == (int)s.size()) no();
	have.insert(calc(get(s, last, s.size() - 1)));
	if (cnt != k) no();
	if (have.size() > 1) no();
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		read();
		run();
		write();
	}
	return 0;
}