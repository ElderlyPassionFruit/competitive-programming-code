#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n;
set<int> all, D, R;
string s;
void read() {
	cin >> n;
	s = "";
	for (int i = 0; i < n; i++) {
		all.insert(i);
		char x;
		cin >> x;
		s += x;
		if (x == 'D')
			D.insert(i);
		if (x == 'R')
			R.insert(i);
	}
}

void run() {
	int pos = 0;
	while (!D.empty() && !R.empty()) {
		if (s[pos] == 'D') {
			auto it = R.lower_bound(pos + 1);
			if (it == R.end())
				it = R.begin();
			int x = *it;
			R.erase(it);
			all.erase(x);	
		}
		if (s[pos] == 'R') {
			auto it = D.lower_bound(pos + 1);
			if (it == D.end())
				it = D.begin();
			int x = *it;
			D.erase(it);
			all.erase(x);
		}
		auto it = all.lower_bound(pos + 1);
		if (it == all.end())
			it = all.begin();
		pos = *it;
	}
}

void write() {
	if (!D.empty())
		cout << "D" << endl;
	else
		cout << "R" << endl;
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