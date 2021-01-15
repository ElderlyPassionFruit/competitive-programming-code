#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

bool cmp(pair <int, int> a, pair <int, int> b) {
	return a.first < b.first || (a.first == b.first && a.second > b.second);
}

vector<pair <int, int> > d;
vector<vector<int> > a;
int m, n, k;

void read() {
	cin >> m >> n >> k;
	d.resize(k);
	for (auto &i : d)
		cin >> i.first >> i.second;
	sort(d.begin(), d.end());
	vector<pair <int, int> > help;
	int r = -1e9;
	for (auto i : d) {
		if (i.second > r) {
			help.push_back(i);
			r = i.second;
		}
	}
	d = help;

	vector<vector<int> > p;
	p.assign(m, vector<int> (2 * n, 0));
	for (auto &i : p)
		for (auto &j : i)
			cin >> j;

	for (int i = 0; i < m; i++) {
		sort(p[i].begin(), p[i].end());
	}

	a.resize(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i].push_back(p[j][i * 2]);
			a[i].push_back(p[j][i * 2 + 1]);
		}
	}

	for (int i = 0; i < n; i++) {
		sort(a[i].begin(), a[i].end());
	}
}

vector<vector<int> > pref, suff;

void calc() {
	pref.assign(n, vector<int> (2 * m));
	for (int i = 0; i < n; i++) {
		pref[i][0] = 0;
		for (int j = 1; j < 2 * m; j++) {
			pref[i][j] = + pref[i][j - 1] + (a[i][j] - a[i][j - 1]) * j;
		}
	}
	suff.assign(n, vector<int> (2 * m));
	for (int i = 0; i < n; i++) {
		suff[i][2 * m - 1] = 0;
		for (int j = 2 * m - 2; j >= 0; j--) {
			suff[i][j] = suff[i][j + 1] + (a[i][j + 1] - a[i][j]) * (2 * m - 1 - j);
		}
	}
}

int ans = 0;

int get(int desk, int pos) {
	int l = d[desk].first;
	int r = d[desk].second;
	int fans = 0;
	if (l > a[pos][0]) {
		int posL = (--lower_bound(a[pos].begin(), a[pos].end(), l)) - a[pos].begin();
		fans += pref[pos][posL] + (l - a[pos][posL]) * (posL + 1);
	}
	if (r < a[pos].back()) {
		int posR = (upper_bound(a[pos].begin(), a[pos].end(), r)) - a[pos].begin();
		fans += suff[pos][posR] + (a[pos][posR] - r) * (2 * m - posR);
	}
	return fans;
}

int add(int pos, int l, int r) {
	pair <int, int> fans = {1e18, 1e18};
	for (int i = l; i <= r; i++) {
		fans = min(fans, {get(i, pos), i});
	}
	ans += fans.first;
	return fans.second;
}

void solve(int l_people, int r_people, int l, int r) {
	if (l_people >= r_people) return;
	int tm = (l_people + r_people) / 2;
	int pos = add(tm, l, r);
	solve(l_people, tm, l, pos);
	solve(tm + 1, r_people, pos, r);
}

void run() {
	calc();	
	solve(0, n, 0, k - 1);
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