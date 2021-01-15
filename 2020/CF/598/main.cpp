#include <bits/stdc++.h>

using namespace std;
#define int long long
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int get(string s) {
	map <char, int> cnt;
	int ans = 0;
	for (auto i : s) {
		for (int j = i + 1; j < 'z'; j++) {
			ans += cnt[j];
		}
		cnt[i]++;
	}
	return ans % 2;
}

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	vector<bool> used(n, false);
	for (int i = 1; i <= n; i++) {
		int pos = 0;
		for (int j = 0; j < n; j++) {
			if (a[j] == i) {
				pos = j;
				break;
			}
		}
		used[pos] = true;
		while (pos - 1 >= 0) {
			if (used[pos - 1]) break;
			used[pos - 1] = true;
			swap(a[pos], a[pos - 1]);
			pos--;
		}
	}
	for (auto i : a)
		cout << i << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}