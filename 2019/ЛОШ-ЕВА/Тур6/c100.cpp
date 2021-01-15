#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector<int> a[3], pref[3], suff[3];
vector<int> help = {1, 1, 1, -1, -1, -1};

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[i % 3].push_back(help[i % 6] * x);
	}
	for (int i = 0; i < 3; i++)
		sort(a[i].begin(), a[i].end());
}


void make() {
	for (int i = 0; i < 3; i++) {
		int sz = a[i].size();
		pref[i].resize(sz);
		suff[i].resize(sz);
		for (int j = 1; j < sz; j++)
			pref[i][j] = pref[i][j - 1] + (a[i][j] - a[i][j - 1]) * j;
		for (int j = sz - 2; j >= 0; j--)
			suff[i][j] = suff[i][j + 1] + (a[i][j + 1] - a[i][j]) * (sz - 1 - j);
	}
}

int calc(int x, int y) {
	vector<int> help = {x, y, y - x};
	int ans = 0;
	
	for (int i = 0; i < 3; i++) {
		int sz = a[i].size();
		if (help[i] <= a[i][0]) {
			ans += suff[i][0] + sz * (a[i][0] - help[i]);
			continue;
		}

		if (help[i] >= a[i].back()) {
			ans += pref[i].back() + sz * (help[i] - a[i].back());
			continue;
		}

		int pos1 = --upper_bound(a[i].begin(), a[i].end(), help[i]) - a[i].begin();
		int pos2 = lower_bound(a[i].begin(), a[i].end(), help[i]) - a[i].begin();

		ans += pref[i][pos1] + suff[i][pos2] + (pos1 + 1) * (help[i] - a[i][pos1]) + (sz - pos2) * (a[i][pos2] - help[i]);
	}
	return ans;
}

int get_ans(int a0) {
	int l1 = -1e9 - 10, r1 = 1e9 + 10;
	while (l1 < r1 - 3) {
		int mid1 = l1 + (r1 - l1) / 3;
		int mid2 = r1 - (r1 - l1) / 3;
		if (calc(a0, mid1) > calc(a0, mid2))
			l1 = mid1;
		else
			r1 = mid2; 
	}

	int ans = 1e18;
	for (int i = l1; i <= r1; i++)
		ans = min(ans, calc(a0, i));
	return ans;
}

int ans = 1e18;

void run() {
	make();
	int l1 = -1e9 - 10, r1 = 1e9 + 10;
	while (l1 < r1 - 3) {
		int mid1 = l1 + (r1 - l1) / 3;
		int mid2 = r1 - (r1 - l1) / 3;
		if (get_ans(mid1) > get_ans(mid2))
			l1 = mid1;
		else
			r1 = mid2; 
	}
	for (int i = l1; i <= r1; i++)
		ans = min(ans, get_ans(i));
}

void write() {
	cout << ans << endl;
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