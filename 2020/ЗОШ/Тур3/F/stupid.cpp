#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
/*
vector<int> build_suff(string & s) {
	s += "#";
	int n = s.size();
	vector<int> a(n);
	iota(all(a), 0);
	sort(all(a), [&] (int i, int j) {return s[i] < s[j];});
	vector<int> c(n);
	int cc = 0;
	for (int i = 0; i < n; i++) {
    
		if (i == 0 || s[a[i]] != s[a[i - 1]])
			c[a[i]] = cc++;
		else
        
			c[a[i]] = c[a[i - 1]];
	}
	for (int l = 1; l < n; l *= 2) {
		vector<int> cnt(n);
		for (auto i : c)
			cnt[i]++;
		vector<int> pref(n);
		for (int i = 1; i < n; i++)
			pref[i] = pref[i - 1] + cnt[i - 1];
		vector<int> na(n);
		for (int i = 0; i < n; i++) {
			int pos = (a[i] - l + n) % n;
			na[pref[c[pos]]++] = pos;
		}
		a = na;
		cc = 0;
		vector<int> nc(n);
		for (int i = 0; i < n; i++) {
			if (i == 0 || c[a[i]] != c[a[i - 1]] || c[(a[i] + l) % n] != c[(a[i - 1] + l) % n])
				nc[a[i]] = cc++;
			else
				nc[a[i]] = nc[a[i - 1]];
		}
		c = nc;
	}
	return a;
}*/

namespace hue{
	const int N = 3e6 + 10;
	int id[N];
	int a[N], b[N];
	string s;

	vector<int> init() {
		for (int i = 0; i < s.size(); ++i) {
			a[i] = s[i];
		}
		a[s.size()] = '#';
		int n = s.size() + 1;
		for (int i = 0; i < n; ++i) {
			id[i] = i;
		} 
		sort(id, id + n, [](int i, int j) {
			return a[i] < a[j];
		});
		for (int t = 0; (1 << t) < n; ++t) {
			for (int i = 0; i < n; ++i) {
				b[i] = a[(i + (1 << t)) % n]; 
			}
			int L = 0, cnt = 0;
			while (L < n) {
				int R = L;
				while (R < n && a[id[L]] == a[id[R]]) {
					++R;
				}
				sort(id + L, id + R, [](int i, int j) {
					return b[i] < b[j];
				});
				a[id[L]] = ++cnt;
				for (int M = L + 1; M < R; ++M) {
					if (b[id[M - 1]] < b[id[M]]) {
						cnt++;
					}
					a[id[M]] = cnt;
				}
				L = R;
			}
		} 
		vector<int> ans;
		for (int i = 0; i < n; i++)
			ans.push_back(id[i]);
		return ans;
		
	}
 
};
vector<int> build_lcp(string & s, vector<int> & a) {
	int n = s.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++)
		ra[a[i]] = i;
	vector<int> lcp(n - 1);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt--;
		chkmax(cnt, 0);
		if (ra[i] + 1 == n) {
			cnt = 0;
			continue;
		}
		int j = a[ra[i] + 1];
		while (s[i + cnt] == s[j + cnt] && s[i + cnt] != '$')
			cnt++;
		lcp[ra[i]] = cnt;
	}
	s.pop_back();
	a.erase(a.begin());
	lcp.erase(lcp.begin());
	return lcp;
}

int n;
vector<string> a;
int m;
vector<string> t;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	cin >> m;
	t.resize(m);
	for (auto &i : t)
		cin >> i;
}

struct Pos{
	int t, pos;
	Pos() {}
	Pos(int a, int b) {
		t = a, pos = b;
	}
};

vector<vector<int> > ans;

vector<Pos> Help;
string s;
vector<int> suff, lcp;

void build() {
	s = "";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)a[i].size(); j++) {
			s += a[i][j];
			Help.push_back({i, j});
		}
		s += "$";
		Help.push_back({-1, -1});
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < (int)t[i].size(); j++) {
			s += t[i][j];
			Help.push_back({n + i, j});
		}
		s += "$";
		Help.push_back({-1, -1});
	}
	hue::s = s;
	suff = hue::init();
	s += "#";
	lcp = build_lcp(s, suff);
	ans.resize(m);
	for (int i = 0; i < m; i++) {
		ans[i].resize(t[i].size());
	}
}

void solve_pref() {
	int last_lcp = 0;
	int sz = s.size();
	for (int i = 0; i < sz; i++) {
		int pos = suff[i];
		if (Help[pos].t < n) {
			if (Help[pos].pos == 0)
				last_lcp = lcp[i];
			else
				chkmin(last_lcp, lcp[i]);
		}
		else {
			int id1 = Help[pos].t - n;
			int id2 = Help[pos].pos;
			chkmax(ans[id1][id2], last_lcp);
			chkmin(last_lcp, lcp[i]);
		}
	}
}

void solve_last() {
	int sz = s.size();
	for (int i = sz - 1; i >= 1; i--)
		lcp[i] = lcp[i - 1];
	lcp[0] = 0;
	int last_lcp = 0;
	for (int i = sz - 1; i >= 0; i--) {
		int pos = suff[i];
		if (Help[pos].t < n) {
			if (Help[pos].pos == 0)
				last_lcp = lcp[i];
			else
				chkmin(last_lcp, lcp[i]);
		}
		else {
			int id1 = Help[pos].t - n;
			int id2 = Help[pos].pos;
			chkmax(ans[id1][id2], last_lcp);
			chkmin(last_lcp, lcp[i]);
		}
	}
}

void run() {
	build();
	lcp.push_back(0);
	solve_pref();
	solve_last();
}

void write() {
	for (auto i : ans) {
		for (auto j : i)
			printf("%d ", j);
		printf("\n");
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