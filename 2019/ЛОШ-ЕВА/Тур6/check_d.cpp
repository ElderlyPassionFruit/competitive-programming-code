#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
//#define int long long
const int MAXN = 1e5 + 10;
const int MAXSQRT = 500;
string s;
int l;
int n, q;
vector<long long> ans;
vector<pair <int, int> > len;

const int MAXNUM = 1 << 23;
int hashs1[MAXNUM];

cc_hash_table<int, int> check;


void add1(int x) {
	check[x] = 1;
	return;
	int pos = x & ((MAXNUM) - 1);
	while (hashs1[pos]) {
		pos++;
		pos &= ((MAXNUM) - 1);
	}
	hashs1[pos] = x;
}

bool check1(int x) {
	return check.find(x) != check.end();
	int pos = x & ((MAXNUM) - 1);
	while (hashs1[pos]) {
		if (hashs1[pos] == x)
			return true;
		pos++;
		pos &= ((MAXNUM) - 1);
	}
	return false;
}

int SQRT[MAXSQRT][MAXN];

const int MOD1 = 1e9 + 7;

const int b1 = 31;

int pows1[MAXN], h1[MAXN];

int get_hash1(string s) {
	int ans = 0;
	int n = s.size();
	for (int i = 1; i <= n; i++) 
		ans = (long long)(ans + (s[i - 1] - 'a' + 1) * pows1[i]) % MOD1;
	return (long long)ans * pows1[l - n] % MOD1;
}

int get_hash1(int l1, int r1) {
	return (long long)((h1[r1] - h1[l1 - 1]) + MOD1) * pows1[l - r1] % MOD1;
}

void make_hashs() {
	pows1[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pows1[i] = (long long)pows1[i - 1] * b1 % MOD1;

	h1[0] = 0;
	for (int i = 1; i <= l; i++)
		h1[i] = (long long)(h1[i - 1] + (s[i - 1] - 'a' + 1) * pows1[i]) % MOD1;
}

void read() {
	cin >> s;
	l = s.size();
	make_hashs();
	cin >> n;
	set<int> help_len;
	for (int i = 0; i < n; i++) {
		string x;
		cin >> x;
		if (x.length() > l) continue;
		add1(get_hash1(x));
		help_len.insert((int)x.length());
	}
	int cnt = 0;
	for (auto i : help_len) {
		len.push_back(make_pair(i, cnt++));
	}
}

void make() {
	for (int i = 1; i <= l; i++) {
		for (auto j : len) {
			if (i + j.first - 1 > l) break;
			int hash1 = get_hash1(i, i + j.first - 1);
			if (check1(hash1))
				SQRT[j.second][i] = 1;
		}
	}

	for (auto j : len) {
		for (int i = 1; i + j.first - 1 <= l; i++) {
			SQRT[j.second][i] = SQRT[j.second][i] + SQRT[j.second][i - 1];
		}
	}
}

int get_ans(pair <int, int> pos, int l1, int r1) {
	if (r1 - pos.first + 1 < l1) return 0;
	return SQRT[pos.second][r1 - pos.first + 1] - SQRT[pos.second][l1 - 1];
}

int get_ans(int l, int r) {
	long long ans = 0;
	for (auto i : len) {
		ans += get_ans(i, l, r);
	}
	return ans;
}

void run() {
	make();

	cin >> q;
	for (int test = 0; test < q; test++) {
		int l, r;
		cin >> l >> r;
		long long fans = get_ans(l, r);
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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