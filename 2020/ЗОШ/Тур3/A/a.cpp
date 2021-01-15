#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;


void read() {
	cin >> n;
}

vector<vector<int> > ans;

void solve(vector<int> a) {
	if (a.size() == 1) return;
	int n = a.size();
	vector<int> a1, a2, a3;
	for (int i = 0; i < n / 3; i++)
		a1.push_back(a[i]);
	for (int i = n / 3; i < 2 * n / 3; i++)
		a2.push_back(a[i]);
	for (int i = 2 * n / 3; i < n; i++)
		a3.push_back(a[i]);

	n /= 3;
	int start = 0;
	for (auto i : a1) {
		for (int j = 0; j < n; j++) {
			ans.push_back({i, a2[j], a3[(start + j) % n]});
		}
		start++;
	}

	solve(a1);
	solve(a2);
	solve(a3);
}

void run() {
	vector<int> a(n);
	iota(all(a), 1);
	//cout << "a = " << endl;
	//for (auto i : a)
	//	cout << i << " ";
	//cout << endl;
	solve(a);
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans) {
		for (auto j : i)
			cout << j << " ";
		cout << "\n";
		//cout << i << "\n";
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