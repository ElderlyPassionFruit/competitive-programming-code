#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

vector<pair<int, int> > ans;

void run() {
	int l = 0, r = 0, sum = 0;
	while (l < n) {
		while (r < n && sum + a[r] <= k && sum < k) {
			sum += a[r];
			r++;
		}
		if (sum == k) {
			ans.push_back({l + 1, r});
		}
		if (r > l) {
			sum -= a[l];
		}
		l++;
		chkmax(r, l);
	}
}

void write() {
	if (ans.size() == 0)
		cout << -1 << endl;
	else {
		sort(all(ans), [&] (pair<int, int> a, pair<int, int> b) {return a.second - a.first < b.second - b.first;});
		cout << ans[0].first << " " << ans[0].second << endl;
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