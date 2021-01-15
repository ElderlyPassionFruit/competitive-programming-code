#include <bits/stdc++.h>

using namespace std;
#define int long long

void wr(int num, string s) {
	cout << "Case #" << num << ": " << s << endl;  	
}

bool check(char a, char b) {
	if (a == 'R' && b == 'S')
		return true;
	if (a == 'S' && b == 'P')
		return true;
	if (a == 'P' && b == 'R')
		return true;
	return false;
}

bool check(string a, string b) {
	int n = a.size();
	int m = b.size();
	string help1 = "";
	for (int i = 0; i < m; i++)
		help1 += a;
	string help2 = "";
	for (int i = 0; i < n; i++)
		help2 += b;
	for (int i = 0; i < help1.size(); i++) {
		if (check(help1[i], help2[i]))
			return true;
		if (check(help2[i], help1[i]))
			return false;
	}
	return false;
}

vector <string> good;

void gen(int len, string s) {
	if (len > 10)
		return;
	good.push_back(s);
	gen(len + 1, s + "R");
	gen(len + 1, s + "P");
	gen(len + 1, s + "S");
}

void solve(int num) {
	int n;
	cin >> n;
	vector <string> t;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		t.push_back(s);
	}
	for (auto x : good) {
		bool flag = true;
		for (auto i : t) {
			if (!check(x, i)) {
				flag = false;
				break;
			}
		}
		if (flag) {
			wr(num, x);
			return;
		}
	}
	wr(num, "IMPOSSIBLE");
}	

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	gen(0, "");
	sort(good.begin(), good.end());
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		solve(i);
	}
	return 0;
}