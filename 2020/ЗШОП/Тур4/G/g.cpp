#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;

int check_split(int l, int r) {
	int bal = 0;
	for (int i = l; i < r; i++) {
		if (s[i] == '(') bal++;
		if (s[i] == ')') bal--;
		if (bal == 0 && s[i] == '|')
			return i; 
	}
	return -1;
}

bool check_make_smaller(int l, int r) {
	int bal = 0;
	for (int i = l; i < r - 1; i++) {
		if (s[i] == '(') bal++;
		if (s[i] == ')') bal--;
		if (bal == 0)
			return false;
	}
	return s[l] == '(';
}

int check_del(int l, int r) {
	int bal = 0;
	for (int i = l; i < r - 1; i++) {
		if (s[i] == '(') bal++;
		if (s[i] == ')') bal--;
		if (bal == 0) {
			if (s[i + 1] == '*')
				return i + 1;
			return -1;
		}
	}
	return -1;
}

int check_add(int l, int r) {
	int bal = 0;
	for (int i = l; i < r - 1; i++) {
		if (s[i] == '(') bal++;
		if (s[i] == ')') bal--;
		if (bal == 0 && s[i + 1] != '*')
			return i;
	}
	return -1;
}

string Min(string a, string b) {
	if (a.size() != b.size()) { 
		if (a.size() < b.size()) return a;
		return b;
	}
	return min(a, b);
}

string solve(int l, int r) {
	//cout << l << " " << r << endl;
	if (r <= l) return "";
	if (l + 1 == r) {
		if (s[l] == '$') return "";
		string ans = "";
		ans += s[l];
		return ans;
	}

	// make smaller
	if (check_make_smaller(l, r)) return solve(l + 1, r - 1);

	int pos;
	
	// split
	pos = check_split(l, r);
	//cout << "split = " << pos << endl;
	if (pos != -1) return Min(solve(l, pos), solve(pos + 1, r));

	// add
	pos = check_add(l, r);
	//cout << "add = " << pos << endl;
	if (pos != -1) return solve(l, pos + 1) + solve(pos + 1, r);

	// del
	pos = check_del(l, r);

	//cout << "del = " << pos << endl;
	if (pos != -1) return solve(pos + 1, r);

	assert(false);
}

void solve() {
	cin >> s;
	string a = "";
	for (auto i : s) {
		if (i != '*' || a[a.size() - 1] != '*')
			a += i; 
	}
	s = a;
	a = "";
	for (auto i : s) {
		if (i >= 'a' && i <= 'c')
			a += "(", a += i, a += ")";
		else
			a += i;
	} 
	s = a;
	s = solve(0, s.size());
	if (s.empty()) s = "$";
	int cnt = 0;
	for (auto i : s)
		cnt += i == '$';
	assert(cnt <= 1);
	assert(!(cnt == 1 && s.size() > 1));
	cout << s << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	//cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}