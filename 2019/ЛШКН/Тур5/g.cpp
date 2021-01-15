#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int l, w;
vector<int> a;
void read() {
	cin >> w >> l;
	a.resize(w - 1);
	for (auto &i : a)
		cin >> i;
}

int ans = 0;

void run() {
	deque<pair <int, int> > st;
	st.push_back({0, 1e9 + 10});
	for (int i = 1; i < w; i++) {
		while (i - st[0].first > l)
			st.pop_front();
		int fans = 0;
		while (!st.empty() && a[i - 1] > 0) {
			int x = min(st[0].second, a[i - 1]);
			a[i - 1] -= x;
			fans += x;
			if (x == st[0].second)
				st.pop_front();
			else
				st[0].second -= x;
		}
		if (fans > 0)
			st.push_back({i, fans});
	}

	while (!st.empty()) {
		if (w - st[0].first <= l)
			ans += st[0].second;
		st.pop_front();
	}
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