#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;
vector<int> b;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	b.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
}

vector<int> solve(vector<int> a, int k) {
	for (int i = 0; i + k - 1 < a.size(); i++) {
		reverse(a.begin() + i, a.begin() + i + k);
	}
	return a;
}

vector<int> ans;

void run() {
	for (int i = 1; i <= n; i++) {
		auto x = solve(a, i);
		//if (x == b)
		//	ans.push_back(i);
		cout << "k = " << i << endl;
		cout << "x = ";
		for (auto j : x)
			cout << j << " ";
		cout << endl;
	}
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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