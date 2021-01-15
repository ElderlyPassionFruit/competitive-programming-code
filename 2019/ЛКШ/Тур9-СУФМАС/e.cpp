#include <bits/stdc++.h>

using namespace std;
#define pb push_back

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9;

vector<int> build_suff(vector<int> & s) {
	s.push_back(-INF);
	int n = s.size();
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		a[i] = i;
	stable_sort(a.begin(), a.end(), [&] (int i, int j) {return s[i] < s[j];});

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
}

vector<int> build_lcp(vector<int> & s, vector<int> & a) {
	int n = a.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++)
		ra[a[i]] = i;
	vector<int> lcp(n - 1);
	int cur = 0;
	for (int i = 0; i < n; i++) {
		cur = max(cur - 1, 0);
		if (ra[i] == n - 1) {
			cur = 0;
			continue;
		}
		int j = a[ra[i] + 1];
		while (s[(i + cur) % n] == s[(j + cur) % n]) {
			cur++;
			if (cur == n)
				break;
		}
		lcp[ra[i]] = cur;
	}
	lcp.erase(lcp.begin());
	a.erase(a.begin());
	s.pop_back();
	return lcp;
}

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> s(n);
	for (auto &i : s)
		cin >> i;
	auto a = build_suff(s);
	auto lcp = build_lcp(s, a);

	vector<int> l(n - 1);
	vector<pair <int, int> > st;
	for (int i = 0; i < n - 1; i++) {
		l[i] = 0;
		while (!st.empty() && st.back().first >= lcp[i]) {
			st.pop_back();
		}
		if (!st.empty())
			l[i] = st.back().second + 1;
		st.push_back({lcp[i], i});
	}

	st.clear();
	vector<int> r(n - 1);
	for (int i = n - 2; i >= 0; i--) {
		r[i] = n - 1;
		while (!st.empty() && st.back().first >= lcp[i]) {
			st.pop_back();
		}
		if (!st.empty())
			r[i] = st.back().second - 1;
		st.push_back({lcp[i], i + 1});
	}

	int pos = 0, len = n, cnt = 1;
	for (int i = 0; i < n - 1; i++) {
		//int l = i;
		//while (l > 0 && lcp[l - 1] >= lcp[i])
		//	l--;
		//int r = i + 1;
		//while (r < n - 1 && lcp[r] >= lcp[i])
		//	r++;
		if ((long long) (r[i] - l[i] + 1) * lcp[i] > (long long) len * cnt) {
			pos = a[i];
			len = lcp[i];
			cnt = (r[i] - l[i] + 1);
		}
	}

	cout << (long long) len * cnt << endl;
	cout << len << endl;
	for (int i = pos; i <= pos + len - 1; i++) {
		cout << s[i] << " ";
	}
	cout << endl;
} 

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	solve();
	return 0;
}