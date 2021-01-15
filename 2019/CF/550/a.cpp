#include <bits/stdc++.h>

using namespace std;
#define int long long

bool check(string s) {
	sort(s.begin(), s.end());
	set <char> x;
	for (int i = 0; i < n; i++) {
		x.insert(s[i]);
	}
	if (x.size() != s.size()) return false;
	for (int i = 0; i < n - 1; i++) {
		if (abs(s[i] - s[i + 1]) != 1) 
			return false;
	}
	return true;
}

void read() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if (check(s))
			cout << "Yes" << endl;
		else 
		{
			cout << "No" << endl;
		}
	}
}

void run() {

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