#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const long long INF = 1e18 + 10;

bool cmp(pair <int, int> &a, pair <int, int> &b) {
	return a.first < b.first || (a.first == b.first && a.second > b.second);
}

vector<pair <int, int> > make(vector<pair <int, int> > a) {
	sort(a.begin(), a.end(), cmp);
	vector<pair <int, int> > ans;
	int R = -1;
	for (auto i : a) {
		if (i.second > R) {
			ans.push_back(i);
			R = i.second;
		}
	}
	return ans;
}

vector<pair <int, int> > desk;

int m, n, k;
vector<vector<int> > p;
void read() {
	cin >> m >> n >> k;
	for (int i = 0; i < k; i++) {
		int l, r;
		cin >> l >> r;
		desk.push_back({l, r});
	}
	desk = make(desk);
	k = desk.size();

	p.assign(n, vector<int> (2 * m, 0));

	for (int i = 0; i < m; i++) {
		vector<int> help(2 * n);
		for (auto &j : help)
			cin >> j;
		sort(help.begin(), help.end());
		for (int j = 0; j < 2 * n; j += 2) {
			p[j / 2][i * 2] = help[j];
			p[j / 2][i * 2 + 1] = help[j + 1];
		}
	}

	for (auto &i : p) {
		sort(i.begin(), i.end());
	}
}

vector<vector<long long> > pref, suff;

void gen() {
	pref.resize(n, vector<long long> (2 * m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < 2 * m; j++) {
			pref[i][j] = pref[i][j - 1] + (long long)(p[i][j] - p[i][j - 1]) * j;
		}
	}

	suff.resize(n, vector<long long> (2 * m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 2 * m - 2; j >= 0; j--) {
			suff[i][j] = suff[i][j + 1] + (long long)(p[i][j + 1] - p[i][j]) * (2 * m - 1 - j);
		}
	}
}

long long get(int pos, int l, int r) {
	long long ans = 0;
	int pos1 = --lower_bound(p[pos].begin(), p[pos].end(), l) - p[pos].begin();
	if (pos1 >= 0) {
		ans += pref[pos][pos1] + (long long)(pos1 + 1) * (l - p[pos][pos1]);
	}
	int pos2 = upper_bound(p[pos].begin(), p[pos].end(), r) - p[pos].begin();
	if (pos2 < 2 * m) {
		ans += suff[pos][pos2] + (long long)(2 * m - pos2) * (p[pos][pos2] - r);
	}
	return ans;
}

long long ans;

void solve(int l_desk, int r_desk, int l_pos, int r_pos) {
	if (l_pos >= r_pos) 
		return;
	int m_pos = (l_pos + r_pos) / 2;
	long long my_ans = INF;
	int best = -1;
	for (int i = l_desk; i <= r_desk; i++) {
		long long fans = get(m_pos, desk[i].first, desk[i].second);
		if (fans < my_ans) {
			my_ans = fans;
			best = i;
		}
	}
	ans += my_ans;
	if (l_pos == r_pos - 1) 
		return;
	solve(l_desk, best, l_pos, m_pos);
	solve(best, r_desk, m_pos + 1, r_pos);
}


void run() {
	gen();
	ans = 0;
	solve(0, k - 1, 0, n);
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