#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n, m;
vector<int> a, b;
void read() {
	cin >> n >> m;
	a.resize(n);
	
	int x = 0;
	for (auto &i : a){
		cin >> i;
		x ^= i;
	}

	b.resize(m);
	for (auto &i : b) {
		cin >> i;
		x ^= i;
	}
	
	if (x != 0) {
		cout << "NO\n";
		exit(0);
	}
}

vector<vector<int> > ans;

void run() {
	ans.assign(n, vector<int> (m, 0));
	
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			int x = a[i];
			ans[i][j] = x;
			a[i] ^= x;
			b[j] ^= x;
		}
	}
	
	for (int j = 0; j < m; j++) {
		ans[n - 1][j] = b[j];
	}
}

void write() {
	cout << "YES\n";
	for (auto i : ans) {
		for (auto j : i)
			cout << j << " ";
		cout << "\n";
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