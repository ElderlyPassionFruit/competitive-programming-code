#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

const int MOD1 = 1e9 + 7, MOD2 = 998244353, 
p1 = 179 + rnd() % 1000, p2 = 971 + rnd() % 1000;

int add(int a, int b, int mod) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

int sub(int a, int b, int mod) {
	a -= b;
	if (a < 0)
		a += mod;
	return a;
}

int mul(int a, int b, int mod) {
	return (a * b) % mod;
}

struct HASH{
	vector<int> h1, h2, pows1, pows2;
	int n;
	HASH() {
		n = 0;
		h1 = {};
		h2 = {};
		pows1 = {};
		pows2 = {};
	}
	HASH(const string & s) {
		n = s.size();
		h1.resize(n + 1);
		h2.resize(n + 1);
		pows1.resize(n + 1);
		pows2.resize(n + 1);
		pows1[0] = 1;
		pows2[0] = 1;
		for (int i = 1; i <= n; i++) {
			pows1[i] = mul(pows1[i - 1], p1, MOD1);
			pows2[i] = mul(pows2[i - 1], p2, MOD2);
		}
		for (int i = 1; i <= n; i++) {
			h1[i] = add(mul(h1[i - 1], p1, MOD1), s[i - 1], MOD1);
			h2[i] = add(mul(h2[i - 1], p2, MOD2), s[i - 1], MOD2);
		}
	}

	pair <int, int> get(int l, int r) {
		return {
			sub(h1[r], mul(h1[l - 1], pows1[r - l + 1], MOD1), MOD1),
			sub(h2[r], mul(h2[l - 1], pows2[r - l + 1], MOD2), MOD2)
		};
	}
};

string s, t;

void read() {
	cin >> s >> t;
}

string get(const string & s) {
	HASH h(s);
	int n = s.size();
	int len_ans = n;
	for (int len = 1; len <= n; len++) {
		bool flag = true;
		for (int i = len + 1; i <= n; i += len) { 
			int my_len = min(len, n - i + 1);
			flag &= (h.get(i, i + my_len - 1) == h.get(1, my_len));
		}
		if (flag)
			chkmin(len_ans, len);
	}
	string ans = "";
	for (int i = 0; i < len_ans; i++)
		ans += s[i];
	return ans;
}

string ans;

void relax(const string s) {
	string fans = get(s);
	if (ans.size() > fans.size())
		ans = fans;
}

string solve(const string & s, const string & t) {
	HASH h1(s), h2(t);
	string help = t;
	int n = s.size(), m = t.size();
	int fans = 0;
	for (int len = 1; len <= min(n, m); len++) {
		if (h1.get(n - len + 1, n) == h2.get(1, len)) {
			fans = len;
		}
	}
	string ans = "";
	ans = s;
	for (int i = fans; i < m; i++)
		ans += t[i];
	return ans;
}

bool check(const string & s, const string & t) {
	HASH h1(s), h2(t);
	int n = s.size(), m = t.size();
	for (int i = 1; i + m - 1 <= n; i++) {
		if (h1.get(i, i + m - 1) == h2.get(1, m)) {
			return true;
		}
	}
	return false;
}

void run() {
	ans = s + t;
	relax(s + t);
	relax(t + s);
	relax(solve(s, t));
	relax(solve(t, s));
	if (check(s, t))
		relax(s);
	if (check(t, s))
		relax(t);
}

void write() {
	cout << (int)ans.length() << endl;
	//cout << ans << endl;
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