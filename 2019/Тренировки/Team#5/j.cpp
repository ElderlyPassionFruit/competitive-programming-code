#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, k;
vector<int> a, b;
void read() {
	cin >> n >> m >> k;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	b.resize(m);
	for (auto &i : b) {
		cin >> i;
	}
}

vector<vector<int> > ans;

void run() {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	int pos1 = 0, pos2 = 0;
	while (pos1 < n) {
		while (pos2 < m && b[pos2] < a[pos1])
			pos2++;
		assert(pos2 < m && b[pos2] == a[pos1]);
		int s = pos1;
		ans.push_back({});
		while (pos1 < n && pos2 < m && a[pos1] == b[pos2] && pos1 - s + 1 <= k) {
			ans[ans.size() - 1].push_back(pos1);
			pos1++;
			pos2++;
		}
	}
}

void write() {
	cout << ans.size() << "\n";
	for (auto &i : ans) {
		cout << i.size() << " ";
		for (auto &j : i)
			cout << j + 1 << " ";
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