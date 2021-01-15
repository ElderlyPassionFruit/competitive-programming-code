#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> build(string & s) {
	s += "$";
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

		int cc = 0;
		vector<int> nc(n);
		for (int i = 0; i < n; i++) {
			if (i == 0 || c[a[i]] != c[a[i - 1]] || c[(a[i] + l) % n] != c[(a[i - 1] + l) % n])
				nc[a[i]] = cc++;
			else
				nc[a[i]] = nc[a[i - 1]];
		}
		c = nc;
	}
	a.erase(a.begin());
	s.pop_back();
	return a;
}

void solve() {
	string s;
	cin >> s;
	long long k;
	cin >> k;

	auto a = build(s);
	int n = a.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++)
		ra[a[i]] = i;

	vector<int> lcp(n);
	int cur = 0;
	for (int i = 0; i < n; i++) {
		cur = max(cur - 1, 0);
		if (ra[i] == n - 1) {
			cur = 0;
			continue;
		}
		int j = a[ra[i] + 1];
		while (i + cur < n && j + cur < n && s[i + cur] == s[j + cur]) 
			cur++;
		lcp[ra[i]] = cur;
	}

	int pos = -1, len = -1;
	long long have = 0;
	int now = 0;
	for (int i = 0; i < n; i++) {
		if ((long long)n - a[i] - now >= k - have) {
			pos = i;
			len = (long long)k - have + now;
			break;
		}
		have += (long long)n - a[i] - now;
		now = lcp[i];
	}

	if (pos == -1) {
		pos = n - 1;
		len = n - a[n - 1];
	}

	for (int i = a[pos]; i < a[pos] + len; i++)
		cout << s[i];
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}