#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

vector<int> solve(int pos) {
	vector<int> ans;
	int cnt = 0;
	int x = 0;
	for (int i = 0; i < n; i++) {
		int now = a[(i + pos) % n];
		if (x & now) {
			ans.push_back(cnt);
			cnt = 0;
			x = 0;
		}
		cnt++;
		x |= now;
	}
	if (cnt)
		ans.push_back(cnt);
	return ans;
}

vector<int> ans;
int pos_ans;

void run() {
	int x = 0;
	ans = solve(n - 1);
	pos_ans = n - 1;
	x = a[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		//cout << "i = " << i << " " << x << " " << a[i] << " " << (x & a[i]) << endl; 
		if (x & a[i]) break;
		x |= a[i];
		auto fans = solve(i);
		if (fans.size() < ans.size())
			ans = fans, pos_ans = i;
	}
	//cout << ((16 | 6) & 8) << endl;
}

void write() {
	cout << ans.size() << " " << pos_ans + 1 << endl;
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