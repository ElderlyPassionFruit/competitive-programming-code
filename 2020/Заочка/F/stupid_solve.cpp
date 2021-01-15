#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, q, k;
vector<int> a;

void read() {
	cin >> n >> q >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int solve(int l, int r) {
	vector<int> x;
	for (int i = l; i <= r; i++)
		x.push_back(a[i]);
	sort(all(x));
	int ans = 1;
	for (int i = 1; i < x.size(); i++)
		ans += x[i] - x[i - 1] > k;
	return ans;
}

vector<int> ans;

void run() {
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		ans.push_back(solve(l, r));
	}
}

void write() {
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