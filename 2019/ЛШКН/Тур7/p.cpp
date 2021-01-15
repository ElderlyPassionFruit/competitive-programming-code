#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e6 + 10;

int n, a;
int cnt[MAXN];
set <pair <int, int> > have;

void solve() {
	cin >> n >> a;
	for (int i = 1; i < MAXN; i++) {
		if (i != a)
		have.insert({0, i});
	}

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (have.find({cnt[x], x}) != have.end()) {
			have.erase({cnt[x], x});
			cnt[x]++;
			have.insert({cnt[x], x});
		}
		else {
			cnt[x]++;
		}
		while (!have.empty() && have.begin()->first < cnt[a]) {
			have.erase(have.begin());
		}
	}

	if (have.empty()) {
		cout << -1 << endl;
	}
	else {
		cout << have.begin()->second << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}