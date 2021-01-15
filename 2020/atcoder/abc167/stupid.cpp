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
vector<pair<int,int>> s;


void check() {
	int bal = 0;
	for (auto i : s) {
		if (bal + i.first < 0) return;
		bal += i.second;
	}
	if (bal != 0) return;
	cerr << "ans = " << endl;
	for (auto i : s) {
		cerr << i.first << " " << i.second << endl;
	}
	cerr << endl;


	/*cerr << "sum = " << endl;
	for (auto i : s) {
		cerr << i.first + i.second << " ";
	}
	cerr << endl;
	cerr << "diff = " << endl;
	for (auto i : s) {
		cerr << i.first - i.second << " ";
	}
	cerr << endl;
	cerr << "abs = " << endl;
	for (auto i : s) {
		cerr << abs(i.first - i.second) << " ";
	}
	cerr << endl;
	cerr << "max = " << endl;
	for (auto i : s) {
		cerr << max(i.first, i.second) << " ";
	}
	cerr << endl;
	cerr << "min = " << endl;
	for (auto i : s) {
		cerr << min(i.first, i.second) << " ";
	}
	cerr << endl;*/
	cerr << "second = " << endl;
	for (auto i : s) {
		cerr << i.second << " ";
	}
	cerr << endl;
	cerr << "first = " << endl;
	for (auto i : s) {
		cerr << i.first << " ";
	}
	cerr << endl;
	cout << "Yes\n";
	//exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	s.resize(n);
	for (auto &i : s)
		i = read_string();
	sort(all(s));
	do {
		check();
	} while (next_permutation(all(s)));
	cout << "No\n";
	return 0;
}