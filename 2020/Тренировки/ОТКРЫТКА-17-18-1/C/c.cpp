#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MAXN = 1e5 + 10;
int p, n, d, b;
vector<int> a;

void read() {
	cin >> p >> n >> d >> b;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

bool check1(int cnt) {
	int pos = n - cnt;
	ll add = 0;
	int r = 0;
	for (int i = 0; i < n; i++) {
		if (i < pos) {
			add += a[i];
			continue;
		}
		chkmax(r, i + 1);
		add += a[i];
		while (r <= min(n - 1, i + d * (i + 1))) {
			add += a[r];
			a[r] = 0;
			r++;
		}
		ll fadd = min(b, add);
		a[i] = fadd;
		if (a[i] != b) {
			return false;
		}
		add -= fadd;
	}
	return true;
}

int ans;

void solve1() {
	int l = 0, r = n + 1;
	vector<int> ra = a;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check1(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
		a = ra;
	}
	ans = n - l;
}

bool check2(int cnt) {
	vector<int> ra = a;
	int pos = (n + 1) / 2 - cnt;
	ll add = 0;
	int r = 0;
	for (int i = 0; i < pos; i++) 
		add += a[i], a[i] = 0;
	pair<int, int> fcheckR = {-1, 0};
	for (int i = pos; i <= (n - 1) / 2; i++) {
		add += a[i];
		a[i] = 0;
		while (r <= min(n - 1, i + (i + 1) * d) && add < b) {
			ll fans = min(b - add, a[r]);
			if (r != fcheckR.first) {
				fcheckR = {r, fans};
			}
			else {
				fcheckR.second += fans;
			}
			add += fans;
			a[r] -= fans;
			if (add != b) r++;
		}
		if (add < b) return false;
		add -= b;
	}
	a = ra;
	pos = (n - 2) / 2 + cnt;
	add = 0;
	int l = n - 1;
	for (int i = n - 1; i > pos; i--) 
		add += a[i], a[i] = 0;
	pair<int, int> fcheckL = {n, 0};
	for (int i = pos; i >= (n + 1) / 2; i--) {
		add += a[i];
		a[i] = 0;
		while (l >= max(0LL, i - (n - i) * d) && add < b) {
			ll fans = min(b - add, a[l]);
			if (l != fcheckL.first) {
				fcheckL = {l, fans};
			}
			else {
				fcheckL.second += fans;
			}
			add += fans;
			a[l] -= fans;
			if (add != b) l--;
		}
		if (add < b) return false;
		add -= b;
	}
	if (fcheckR.first > fcheckL.first) return false;
	if (fcheckR.first < fcheckL.first) return true;
	return ra[fcheckL.first] >= fcheckL.second + fcheckR.second;
}

void solve2() {
	int l = 0, r = (n + 1) / 2 + 1;
	vector<int> ra = a;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check2(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
		a = ra;
	}
	ans = (n + 1) / 2 - l;
}

void run() {
	if (p == 1) {
		solve1();
	}
	else if (p == 2) {
		solve2();
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