#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> build_suff(string & s) {
	s += '#';
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
		vector<int> nc(n);
		cc = 0;
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

vector<int> build_lcp(string & s, vector<int> & a) {
	int n = s.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++) {
		ra[a[i]] = i;
	}
	int cnt = 0;
	vector<int> lcp(n - 1);
	for (int i = 0; i < n; i++) {
		cnt--;
		chkmax(cnt, 0);
		if (ra[i] == n - 1) {
			cnt = 0;
			continue;
		}
		int j = a[ra[i] + 1];
		while (s[(i + cnt) % n] == s[(j + cnt) % n])
			cnt++;
		lcp[ra[i]] = cnt;
	}
	s.pop_back();
	a.erase(a.begin());
	lcp.erase(lcp.begin());
	return lcp;
}

int n;
string s;
void read() {
	cin >> n >> s;
}

vector<int> pref_bal;
vector<int> next_pos;
vector<vector<int> > fbal;

void build_bal() {
	fbal.resize(2 * n + 10);
	pref_bal.resize(n);
	int bal = 0;
	for (int i = 0; i < n; i++) {
		pref_bal[i] = bal;
		if (s[i] == '(')
			bal++;
		else
			bal--;
		fbal[bal + n].push_back(i);
	}

	vector<int> pos(2 * n + 10, n);
	
	next_pos.resize(n);

	for (int i = n - 1; i >= 0; i--) {
		next_pos[i] = pos[pref_bal[i] - 1 + n];
		pos[pref_bal[i] + n] = i;
	}
}

long long ans;

void run() {
	build_bal();
	auto a = build_suff(s);
	auto lcp = build_lcp(s, a);

	ans = 0;

	int last = 0;
	for (int i = 0; i < n - 1; i++) {
		if (s[a[i]] == ')')
			break;
		int pos_s = a[i] + last;
		int pos_f = next_pos[a[i]];
		int ind = pref_bal[a[i]] + n;
		int l = lower_bound(fbal[ind].begin(), fbal[ind].end(), pos_s) - fbal[ind].begin();
		int r = lower_bound(fbal[ind].begin(), fbal[ind].end(), pos_f) - fbal[ind].begin();
		if (r > l)
			ans += r - l;
		last = lcp[i];			
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