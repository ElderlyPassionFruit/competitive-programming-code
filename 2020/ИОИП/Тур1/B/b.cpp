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

struct segment{
	int l, r;
	segment() {}
	segment(int _l, int _r) {
		l = _l, r = _r;
	}
};

vector<segment> x;
vector<int> cnt_pref, cnt_suff;
vector<int> used;

int sz;
void build() {
	vector<int> have;
	for (auto i : a)
		have.push_back(i);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &i : a)
		i = lower_bound(all(have), i) - have.begin();  
	sz = have.size();
	vector<int> l(sz), r(sz);
	for (int i = 0; i < n; i++)
		r[a[i]] = i;
	for (int i = n - 1; i >= 0; i--)
		l[a[i]] = i;
	for (int i = 0; i < sz; i++) {
		x.push_back({l[i], r[i]});
	}

	
	used.assign(sz, 0);
	cnt_pref.resize(sz);

	for (int i = 0; i < n; i++) {
		if (a[i] > 0 && !used[a[i]]) {
			cnt_pref[a[i]] = used[a[i] - 1];
		}
		used[a[i]]++;
	}

	used.assign(sz, 0);
	cnt_suff.resize(sz);
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] < have.size() - 1 && !used[a[i]]) {
			cnt_suff[a[i]] = used[a[i] + 1];
		}
		used[a[i]]++;
	}
} 

int ans;

void half() {
	vector<int> pref(n, 0);
	vector<int> cnt(sz, 0);
	for (int i = 0; i < n; i++) {
		cnt[a[i]]++;
		pref[i] = cnt[a[i]];
	}
	cnt.assign(sz, 0);
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] + 1 < sz) {
			chkmax(ans, pref[i] + cnt[a[i] + 1]);
		}
		cnt[a[i]]++;
	}
}

void run() {
	build();
	ans = 0;
	half();
	vector<int> dp(sz, 0);

	for (int i = 0; i < sz; i++) {
		int fans = used[i];
		chkmax(dp[i], fans + cnt_pref[i]);
		if (i > 0 && x[i - 1].r < x[i].l)
			chkmax(dp[i], fans + dp[i - 1]);
		chkmax(ans, dp[i] + cnt_suff[i]);
	}
	ans = n - ans;
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

/*
14
8 9 1 9 9 5 5 5 5 2 8 8 5 3 



*/