#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

string gen1(int n) {
	string ans = "";
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			ans += "9";
		}
		else {
			ans += "0";
		}
	}
	return ans;
} 

string gen2(int n) {
	string ans = "1";
	n--;
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			ans += "9";
		}
		else {
			ans += "0";
		}
	}
	return ans;
} 

void fi() {
	cout << "First";
	exit(0);
}

void se() {
	cout << "Second";
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	string s;
	cin >> s;
	int n = s.size();
	string f;
	if (n % 2) {
		f = gen1(n);
		if (f >= s) {
			fi();
		}
		else {
			se();
		}
	}
	else {
		f = gen2(n);
		if (f >= s) {
			se();
		}
		else {
			fi();
		}
	}
	return 0;
}

