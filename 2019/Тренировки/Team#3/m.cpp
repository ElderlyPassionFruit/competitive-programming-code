#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string a, b, c;

void read() {
	cin >> a >> b >> c;
}

bool ans;

void run() {
	vector<int> pos;
	int n = a.size();
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i] || a[i] != c[i] || b[i] != c[i])
			pos.push_back(i);  
	}
	if (pos.size() > 3) {
		ans = false;
		return;
	}

	if (pos.size() <= 1) {
		ans = true;
		return;
	}

	if (ans.size() == 2) {

	}

	if (ans.size() == 3) {
		
	}
	ans = true; 
}

void write() {
	if (ans) {
		cout << "Ambiguous" << endl;
	}
	else {
		cout << "Impossible" << endl;
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