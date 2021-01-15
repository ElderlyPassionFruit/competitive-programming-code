#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
	cin >> n;
}

string ans;
int sz;

const int MAXN = 1e6 + 10;
int pows[MAXN], h1[MAXN], h2[MAXN];
int pows2[MAXN], H1[MAXN], H2[MAXN];
const int MOD = 1791791791;
const int MOD2 = 1e9 + 7;
int p = 179 + rand();
int p2 = 130 + rand();

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	return a * b % MOD;
}

void make() {
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++)  
		pows[i] = mul(pows[i - 1], p);

	pows2[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pows2[i] = mul(pows2[i - 1], p2);

	h1[0] = 0;
	sz = ans.size();
	for (int i = 1; i <= sz; i++) {
		h1[i] = add(mul(h1[i - 1], p), ans[i - 1]);
	}

	H1[0] = 0;
	for (int i = 1; i <= sz ; i++) {
		H1[i] = add(mul(H1[i - 1], p2), ans[i - 1]);
	}
}

int get1(int l, int r) {
	return sub(h1[r], mul(h1[l - 1], pows[r - l + 1]));
}

int GET1(int l, int r) {
	return sub(H1[r], mul(H1[l - 1], pows2[r - l + 1]));
}

int get2(int l, int r) {
	return sub(h2[r], mul(h2[l - 1], pows[r - l + 1]));
}

int GET2(int l, int r) {
	return sub(H2[r], mul(H2[l - 1], pows2[r - l + 1]));
}

bool check(int l1, int r1, int l2, int r2) {
	return get1(l1, r1) == get2(l2, r2) && GET1(l1, r1) == GET2(l2, r2);
}

void add(string & s) {
	for (int i = 1; i <= s.size(); i++) {
		h2[i] = add(mul(h2[i - 1], p), s[i - 1]);
		H2[i] = add(mul(H2[i - 1], p2), s[i - 1]);
	}

	int len = 0;
	for (int i = 1; i <= min((int) s.size(), sz); i++) {
		if (check(sz - i + 1, sz, 1, i)) {
			len = i;
		}
	}

	reverse(s.begin(), s.end());
	while (len) {
		s.pop_back();
		len--;
	}
	reverse(s.begin(), s.end());
	ans += s;
	for (int i = sz + 1; i <= ans.size(); i++) {
		h1[i] = add(mul(h1[i - 1], p), ans[i - 1]);
		H1[i] = add(mul(H1[i - 1], p2), ans[i - 1]);
	}
	sz = ans.size();
}

void run() {
	cin >> ans;
	make();
	for (int i = 0; i < n - 1; i++) {
		string x;
		cin >> x;
		add(x);
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