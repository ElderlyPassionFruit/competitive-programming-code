#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int INF = 1e9;
int n, m;
string s, t;

void read() {
	cin >> s >> t;
	n = s.size();
	m = t.size();
}

vector<int> make(string s, string t) {
	int n = s.size();
	int m = t.size();
	vector<int> ans(m, INF);
	int pos = 0;
	for (int i = 0; i < m; i++) {
		while (pos < n && s[pos] != t[i])
			pos++;
		if (pos < n) {
			ans[i] = pos++;
		}
	}
	return ans;
}

vector<int> fl, fr;

bool check(int len_del) {
	if (len_del == m)
		return true;
	if (fl[m - 1 - len_del] < n)
		return true;
	if (fr[len_del] >= 0)
		return true;
	for (int i = 0; i + len_del + 1 < m; i++) {
		if (fl[i] < fr[i + len_del + 1])
			return true;
	}
	return false;
}

string get(string s, int l, int r) {
	string ans = "";
	for (int i = l; i <= r; i++)
		ans += s[i];
	return ans;
}

string get_ans(int len_del) {
	if (len_del == m) {
		return "-";
	}
	if (fl[m - 1 - len_del] < n)
		return get(t, 0, m - 1 - len_del);
	if (fr[len_del] >= 0)
		return get(t, len_del, m - 1);
	for (int i = 0; i + len_del + 1 < m; i++) {
		if (fl[i] < fr[i + len_del + 1])
			return get(t, 0, i) + get(t, i + len_del + 1, m - 1);
	}
	assert(false);
}

string ans;

void run() {
	fl = make(s, t);
	reverse(s.begin(), s.end());
	reverse(t.begin(), t.end());
	fr = make(s, t);
	reverse(s.begin(), s.end());
	reverse(t.begin(), t.end());
	reverse(fr.begin(), fr.end());
	for (auto &i : fr) {
		if (i != INF) {
			i = n - 1 - i;
		}
		else {
			i = -INF;
		}
	}
	int l = -1, r = m;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = get_ans(r);
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